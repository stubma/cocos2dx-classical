//
//  lpk.c
//  lpk
//
//  Created by maruojie on 15/2/15.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#include "lpk.h"
#include <stdlib.h>
#include "hash_bob_jenkins_v2.h"
#include <string.h>
#include <zlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
static int lpk_decompress_zlib(uint8_t* in, uint32_t inLength, uint8_t** out, uint32_t* outLength) {
    // ret value
    int err = Z_OK;
    
    // init buffer to 256k
    int bufferSize = 256 * 1024;
    *out = (uint8_t*)malloc(bufferSize * sizeof(uint8_t));
    
    // zlib stream struct
    z_stream d_stream;
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;
    d_stream.next_in  = in;
    d_stream.avail_in = inLength;
    d_stream.next_out = *out;
    d_stream.avail_out = bufferSize;
    
    /* window size to hold 256k */
    if((err = inflateInit2(&d_stream, 15 + 32)) != Z_OK) {
        return err;
    }
    
    // inflate loop until error or done
    while(1) {
        // inflate
        err = inflate(&d_stream, Z_NO_FLUSH);
        
        // if end, break
        if (err == Z_STREAM_END) {
            break;
        }
        
        // check other error
        switch (err) {
            case Z_NEED_DICT:
                err = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&d_stream);
                return err;
        }
        
        // not enough memory?
        if (err != Z_STREAM_END) {
            *out = (unsigned char*)realloc(*out, bufferSize * 2);
            
            // not enough memory, ouch
            if (! *out ) {
                inflateEnd(&d_stream);
                return Z_MEM_ERROR;
            }
            
            // adjust stream
            d_stream.next_out = *out + bufferSize;
            d_stream.avail_out = bufferSize;
            bufferSize *= 2;
        }
    }
    
    // end and return
    *outLength = bufferSize - d_stream.avail_out;
    err = inflateEnd(&d_stream);
    return err;
}
    
// decompress function define
typedef int (*LPK_DECOMPRESS)(uint8_t*, uint32_t, uint8_t**, uint32_t*);
    
// decompress table define
typedef struct {
    // decompression bit
    uint32_t mask;
    
    // decompression function
    LPK_DECOMPRESS decompress;
} LPKDecompressTable;
    
// decompress table
static LPKDecompressTable s_dcmp_table[] = {
    LPKC_NONE, NULL,
    LPKC_ZLIB, lpk_decompress_zlib
};
    
int lpk_open_file(lpk_file* lpk, const char* filepath) {
    // result code
    int result = 0;
    
    // to avoid goto with do-while wrapper
    do {
        // try to open file
        if ((lpk->fp = fopen(filepath, "rb")) == NULL) {
            result = LPK_ERROR_OPEN;
            break;
        }
        
        // read header from file
        if(fread(&lpk->h, sizeof(lpk_header), 1, lpk->fp) != 1) {
            result = LPK_ERROR_FORMAT;
            break;
        }
        
        // check if we found a valid lpk header
        if(lpk->h.lpk_magic != LPK_MAGIC) {
            result = LPK_ERROR_FORMAT;
            break;
        }
        
        // allocate memory for the block table, hash table
        if((lpk->bet = calloc(lpk->h.block_table_count, sizeof(lpk_block))) == NULL ||
           (lpk->het = calloc(lpk->h.hash_table_count, sizeof(lpk_hash))) == NULL) {
            result = LPK_ERROR_MALLOC;
            break;
        }
        
        // seek to hash table
        if(fseeko(lpk->fp, lpk->h.hash_table_offset, SEEK_SET) < 0) {
            result = LPK_ERROR_SEEK;
            break;
        }
        
        // read the hash table into the buffer
        if(fread(lpk->het, sizeof(lpk_hash), lpk->h.hash_table_count, lpk->fp) != lpk->h.hash_table_count) {
            result = LPK_ERROR_READ;
            break;
        }
        
        // seek to block table
        if(fseeko(lpk->fp, lpk->h.block_table_offset, SEEK_SET) < 0) {
            result = LPK_ERROR_SEEK;
            break;
        }
        
        // read block table into buffer
        if(fread(lpk->bet, sizeof(lpk_block), lpk->h.block_table_count, lpk->fp) != lpk->h.block_table_count) {
            result = LPK_ERROR_READ;
            break;
        }
    } while(0);
    
    return result;
}

int lpk_close_file(lpk_file* lpk) {
    /* try to close the file */
    if(fclose(lpk->fp) < 0) {
        /* don't free anything here, so the caller can try calling us
         * again.
         */
        return LPK_ERROR_CLOSE;
    }
    
    /* free header, tables and list. */
    free(lpk->het);
    free(lpk->bet);
    
    /* if no error was found, return zero. */
    return LPK_SUCCESS;
}
    
uint32_t lpk_get_file_hash_table_index(lpk_file* lpk, const char* filepath) {
    // get hash
    size_t pathLen = strlen(filepath);
    uint32_t hashI = hashlittle(filepath, pathLen, LPK_HASH_TAG_TABLE_INDEX) & (lpk->h.hash_table_count - 1);
    uint32_t hashA = hashlittle(filepath, pathLen, LPK_HASH_TAG_NAME_A);
    uint32_t hashB = hashlittle(filepath, pathLen, LPK_HASH_TAG_NAME_B);
    
    // find start entry
    lpk_hash* hash = lpk->het + hashI;
    while((hash->hash_a != hashA || hash->hash_b != hashB) && hash->next_hash != LPK_HASH_FREE) {
        hashI = hash->next_hash;
        hash = lpk->het + hashI;
    }
    
    // return
    if(hash->hash_a != hashA || hash->hash_b != hashB) {
        return LPK_HASH_FREE;
    } else {
        return hashI;
    }
}
    
uint32_t lpk_get_file_block_table_index(lpk_file* lpk, const char* filepath) {
    // find hash index
    uint32_t hashIndex = lpk_get_file_hash_table_index(lpk, filepath);
    if(hashIndex == LPK_HASH_FREE) {
        return LPK_BLOCK_INVALID;
    }
    
    // get block index from hash
    lpk_hash* hash = lpk->het + hashIndex;
    return hash->block_table_index;
}
    
uint32_t lpk_get_file_size(lpk_file* lpk, const char* filepath) {
    // find block index
    uint32_t blockIndex = lpk_get_file_block_table_index(lpk, filepath);
    if(blockIndex == LPK_BLOCK_INVALID) {
        return 0;
    }
    
    // get block
    lpk_block* block = lpk->bet + blockIndex;
    
    // return
    return block->file_size;
}
    
uint8_t* lpk_extract_file(lpk_file* lpk, const char* filepath, uint32_t* size) {
    // init size
    if(size) {
        *size = 0;
    }
    
    // find hash index
    uint32_t hashIndex = lpk_get_file_hash_table_index(lpk, filepath);
    if(hashIndex == LPK_HASH_FREE) {
        return NULL;
    }
    
    // find block index
    lpk_hash* hash = lpk->het + hashIndex;
    uint32_t blockIndex = hash->block_table_index;
    
    // get block
    lpk_block* block = lpk->bet + blockIndex;
    
    // if not exist, return
    if(!(block->flags & LPK_FLAG_EXISTS)) {
        return NULL;
    }
    
    // seek
    if(fseeko(lpk->fp, sizeof(lpk_header) + block->offset, SEEK_SET) < 0) {
        return NULL;
    }
    
    // allocate memory
    uint8_t* buf = (uint8_t*)malloc(sizeof(uint8_t) * block->packed_size);
    
    // read, if failed, release buffer
    if(fread(buf, block->packed_size, 1, lpk->fp) != 1) {
        free(buf);
        buf = NULL;
    }
    
    // TODO decrypt
    
    // uncompress
    if(block->flags & LPK_FLAG_COMPRESSED) {
        
    }
    
    // save size
    if(size) {
        *size = block->file_size;
    }
    
    // return
    return buf;
}

#ifdef __cplusplus
}
#endif