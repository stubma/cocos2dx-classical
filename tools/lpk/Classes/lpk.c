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
#include "tea.h"
#include "xxtea.h"

#ifdef __cplusplus
extern "C" {
#endif
    
static uint32_t next_pot(uint32_t x) {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}
    
static uint32_t lpk_get_file_hash_table_index_by_hash(lpk_file* lpk, uint32_t hash_i, uint32_t hash_a, uint32_t hash_b, uint16_t locale, LPKPlatform platform) {
    // find start entry
    uint32_t hashI = hash_i & (lpk->h.hash_table_count - 1);
    lpk_hash* hash = lpk->het + hashI;
    while((hash->hash_a != hash_a || hash->hash_b != hash_b || hash->locale != locale || hash->platform != platform) && hash->next_hash != LPK_INDEX_INVALID) {
        hashI = hash->next_hash;
        hash = lpk->het + hashI;
    }
    
    // return
    if((hash->hash_a != hash_a) || (hash->hash_b != hash_b) || !(hash->flags & LPK_FLAG_USED) || (hash->flags & LPK_FLAG_DELETED)) {
        return LPK_INDEX_INVALID;
    } else {
        return hashI;
    }
}
    
static uint32_t lpk_delete_hash(lpk_file* lpk, uint32_t hashIndex) {
    // mark
    lpk_hash* hash = lpk->het + hashIndex;
    hash->flags |= LPK_FLAG_DELETED;
    
    // fix prev hash next link
    if(hash->prev_hash != LPK_INDEX_INVALID) {
        lpk->het[hash->prev_hash].next_hash = hash->next_hash;
    }
    
    // swap hash and next hash
    lpk_hash* nextHash = hash->next_hash == LPK_INDEX_INVALID ? NULL : (lpk->het + hash->next_hash);
    if(nextHash) {
        lpk_hash tmp;
        memcpy(&tmp, hash, sizeof(lpk_hash));
        memcpy(hash, nextHash, sizeof(lpk_hash));
        hash->prev_hash = tmp.prev_hash;
        memcpy(nextHash, &tmp, sizeof(lpk_hash));
        return tmp.next_hash;
    } else {
        return hashIndex;
    }
}
    
static uint32_t lpk_find_deleted_hash(lpk_file* lpk, int blockCount) {
    if(lpk->h.deleted_hash != LPK_INDEX_INVALID) {
        uint32_t blockSize = 512 << lpk->h.block_size;
        int hashIndex = lpk->h.deleted_hash;
        while(hashIndex != LPK_INDEX_INVALID) {
            // if block matched, return
            lpk_hash* hash = lpk->het + hashIndex;
            int hashBlocks = (hash->packed_size + blockSize - 1) / blockSize;
            if(blockCount <= hashBlocks) {
                return hashIndex;
            }
            
            // next hash
            hashIndex = hash->next_hash;
        }
    }
    
    return LPK_INDEX_INVALID;
}
    
static void lpk_release_deleted_hash(lpk_file* lpk, uint32_t deletedHashIndex) {
    // unlink
    lpk_hash* deleted_hash = lpk->het + deletedHashIndex;
    if(deleted_hash->prev_hash == LPK_INDEX_INVALID) {
        lpk->h.deleted_hash = deleted_hash->next_hash;
    } else {
        lpk->het[deleted_hash->prev_hash].next_hash = deleted_hash->next_hash;
    }
    if(deleted_hash->next_hash != LPK_INDEX_INVALID) {
        lpk->het[deleted_hash->next_hash].prev_hash = deleted_hash->prev_hash;
    }
    
    // flag it as unused
    memset(deleted_hash, 0, sizeof(lpk_hash));
}
    
static void lpk_link_deleted_hash(lpk_file* lpk, uint32_t hashIndex) {
    lpk_hash* deleted_hash = lpk->het + hashIndex;
    if(lpk->h.deleted_hash == LPK_INDEX_INVALID) {
        lpk->h.deleted_hash = hashIndex;
        deleted_hash->next_hash = LPK_INDEX_INVALID;
        deleted_hash->prev_hash = LPK_INDEX_INVALID;
    } else {
        // find insert point
        int insertBeforeHashIndex = lpk->h.deleted_hash;
        while(insertBeforeHashIndex != LPK_INDEX_INVALID) {
            lpk_hash* hash = lpk->het + insertBeforeHashIndex;
            if(deleted_hash->packed_size <= hash->packed_size) {
                break;
            }
             
            // next hash
            insertBeforeHashIndex = hash->next_hash;
        }
        
        // insert
        lpk_hash* hash = lpk->het + insertBeforeHashIndex;
        deleted_hash->next_hash = insertBeforeHashIndex;
        if(hash->prev_hash == LPK_INDEX_INVALID) {
            lpk->h.deleted_hash = hashIndex;
        } else {
            lpk->het[hash->prev_hash].next_hash = hashIndex;
        }
        deleted_hash->prev_hash = hash->prev_hash;
        hash->prev_hash = hashIndex;
    }
}

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
    
static int lpk_decrypt_xor(uint8_t* enc, uint32_t encLen, const uint8_t* key, const uint32_t keyLen, uint8_t** out, uint32_t* outLen) {
    *out = (uint8_t*)malloc(sizeof(uint8_t) * encLen);
    memcpy(*out, enc, sizeof(uint8_t) * encLen);
    for(int i = 0; i < encLen; i += keyLen) {
        int remain = (keyLen < encLen - i) ? keyLen : (encLen - i);
        for(int j = 0; j < remain; j++) {
            (*out)[i + j] ^= key[j];
        }
    }
    if(outLen) {
        *outLen = encLen;
    }
    return 0;
}
    
static int lpk_decrypt_tea(uint8_t* enc, uint32_t encLen, const uint8_t* key, const uint32_t keyLen, uint8_t** out, uint32_t* outLen) {
    *out = (uint8_t*)teadec((const char*)key, keyLen, (const char*)enc, encLen, 0, encLen, (int*)outLen);
    return 0;
}

static int lpk_decrypt_xxtea(uint8_t* enc, uint32_t encLen, const uint8_t* key, const uint32_t keyLen, uint8_t** out, uint32_t* outLen) {
    *out = (uint8_t*)xxtea_decrypt((unsigned char*)enc, (xxtea_long)encLen, (unsigned char*)key, (xxtea_long)keyLen, (xxtea_long*)outLen);
    return 0;
}
    
// decompress function define
typedef int (*LPK_DECOMPRESS)(uint8_t*, uint32_t, uint8_t**, uint32_t*);
    
// decompress table
static LPK_DECOMPRESS s_dcmp_table[] = {
    NULL, // LPKC_DEFAULT
    NULL, // LPKC_NONE
    lpk_decompress_zlib, // LPKC_ZLIB
};
    
// decrypt function define
typedef int (*LPK_DECRYPT)(uint8_t*, uint32_t, const uint8_t*, const uint32_t, uint8_t**, uint32_t*);
    
// decrypt table
static LPK_DECRYPT s_dcyt_table[] = {
    NULL, // LPKE_DEFAULT,
    NULL, // LPKE_NONE,
    lpk_decrypt_xor, // LPKE_XOR,
    lpk_decrypt_tea, // LPKE_TEA,
    lpk_decrypt_xxtea // LPKE_XXTEA
};
    
static int lpk_copy_hash(lpk_file* lpk, uint32_t dstHashIndex, lpk_hash* srcHash,
                          const uint8_t* packedData, uint32_t offset) {
    // seek
    if(fseeko(lpk->fp, offset, SEEK_SET) < 0) {
        return LPK_ERROR_SEEK;
    }
    
    // write
    if(fwrite(packedData, srcHash->packed_size, 1, lpk->fp) != 1) {
        return LPK_ERROR_WRITE;
    }
    
    // get hash
    lpk_hash* hash = lpk->het + dstHashIndex;
    
    // copy
    memcpy(hash, srcHash, sizeof(lpk_hash));
    
    // adjust info
    hash->next_hash = LPK_INDEX_INVALID;
    hash->prev_hash = LPK_INDEX_INVALID;
    hash->offset = offset - sizeof(lpk_header);
    
    return LPK_SUCCESS;
}
    
static uint32_t lpk_next_free_hash_index(lpk_file* lpk, uint32_t from) {
    for(int i = from; i < lpk->h.hash_table_count; i++) {
        if(!(lpk->het[i].flags & LPK_FLAG_USED)) {
            return i;
        }
    }
    for(int i = 0; i < from; i++) {
        if(!(lpk->het[i].flags & LPK_FLAG_USED)) {
            return i;
        }
    }
    return LPK_INDEX_INVALID;
}

static void lpk_rebuild_hash(lpk_file* lpk, uint32_t newCount) {
    // save new count
    uint32_t oldCount = lpk->h.hash_table_count;
    lpk->h.hash_table_count = newCount;
    
    // allocate memory for new hash table
    lpk_hash* het = (lpk_hash*)calloc(newCount, sizeof(lpk_hash));
    
    // first iterator heads of link
    lpk_hash* oldHash = lpk->het;
    for(int i = 0; i < oldCount; i++, oldHash++) {
        if((oldHash->flags & LPK_FLAG_USED) && !(oldHash->flags & LPK_FLAG_DELETED) && oldHash->prev_hash == LPK_INDEX_INVALID) {
            uint32_t hashIndex = oldHash->hash_i & (newCount - 1);
            lpk_hash* newHash = het + hashIndex;
            memcpy(newHash, oldHash, sizeof(lpk_hash));
            newHash->prev_hash = LPK_INDEX_INVALID;
            newHash->next_hash = LPK_INDEX_INVALID;
        }
    }
    
    // then iterate non-head of link
    uint32_t freeHashIndex = 0;
    oldHash = lpk->het;
    for(int i = 0; i < oldCount; i++, oldHash++) {
        if((oldHash->flags & LPK_FLAG_USED) && !(oldHash->flags & LPK_FLAG_DELETED) && oldHash->prev_hash == LPK_INDEX_INVALID) {
            uint32_t prevHashIndex = oldHash->hash_i & (newCount - 1);
            lpk_hash* newPrev = het + prevHashIndex;
            lpk_hash* oldPrev = oldHash;
            while(oldPrev->next_hash != LPK_INDEX_INVALID) {
                oldPrev = lpk->het + oldPrev->next_hash;
                freeHashIndex = lpk_next_free_hash_index(lpk, freeHashIndex);
                memcpy(het + freeHashIndex, oldPrev, sizeof(lpk_hash));
                newPrev->next_hash = freeHashIndex;
                newPrev = het + freeHashIndex;
                newPrev->prev_hash = prevHashIndex;
                newPrev->next_hash = LPK_INDEX_INVALID;
                prevHashIndex = freeHashIndex;
            }
        }
    }
    
    // iterate deleted hash
    oldHash = lpk->het;
    for(int i = 0; i < oldCount; i++, oldHash++) {
        if((oldHash->flags & LPK_FLAG_USED) && (oldHash->flags & LPK_FLAG_DELETED) && oldHash->prev_hash == LPK_INDEX_INVALID) {
            // copy head
            freeHashIndex = lpk_next_free_hash_index(lpk, freeHashIndex);
            memcpy(het + freeHashIndex, oldHash, sizeof(lpk_hash));
            oldHash->next_hash = LPK_INDEX_INVALID;
            oldHash->prev_hash = LPK_INDEX_INVALID;
            lpk->h.deleted_hash = freeHashIndex;
            
            // copy link
            uint32_t prevHashIndex = freeHashIndex;
            lpk_hash* newPrev = het + prevHashIndex;
            lpk_hash* oldPrev = oldHash;
            while(oldPrev->next_hash != LPK_INDEX_INVALID) {
                oldPrev = lpk->het + oldPrev->next_hash;
                freeHashIndex = lpk_next_free_hash_index(lpk, freeHashIndex);
                memcpy(het + freeHashIndex, oldPrev, sizeof(lpk_hash));
                newPrev->next_hash = freeHashIndex;
                newPrev = het + freeHashIndex;
                newPrev->prev_hash = prevHashIndex;
                newPrev->next_hash = LPK_INDEX_INVALID;
                prevHashIndex = freeHashIndex;
            }
            
            break;
        }
    }
    
    // set new hash table
    free(lpk->het);
    lpk->het = het;
}
    
static const uint8_t* lpk_get_file_packed_data(lpk_file* lpk, lpk_hash* hash) {
    // seek
    if(fseeko(lpk->fp, hash->offset + sizeof(lpk_header), SEEK_SET) > 0) {
        return NULL;
    }
    
    // read out new file data
    uint8_t* fileData = (uint8_t*)malloc(sizeof(uint8_t) * hash->packed_size);
    if(fread(fileData, hash->packed_size, 1, lpk->fp) != 1) {
        free(fileData);
        return NULL;
    }
    
    return fileData;
}
    
static uint32_t lpk_save_patch_file(lpk_file* lpk, lpk_file* patch, uint32_t dstHashIndex, lpk_hash* patchHash) {
    // read out new file data
    const uint8_t* fileData = lpk_get_file_packed_data(patch, patchHash);
    if(!fileData) {
        return 0;
    }
    
    // copy patch hash, reused deleted blocks or add new file to archive end
    uint32_t blockSize = 512 << lpk->h.block_size;
    int blockCount = (patchHash->packed_size + blockSize - 1) / blockSize;
    uint32_t deletedHashIndex = lpk_find_deleted_hash(lpk, blockCount);
    if(deletedHashIndex == LPK_INDEX_INVALID) {
        lpk_copy_hash(lpk, dstHashIndex, patchHash, fileData, lpk->h.hash_table_offset);
        lpk->h.hash_table_offset += blockCount * blockSize;
    } else {
        // if deleted hash block is larger, need save extra blocks
        // if just same, remove deleted hash
        lpk_hash* deletedHash = lpk->het + deletedHashIndex;
        uint32_t fileOffset = deletedHash->offset + sizeof(lpk_header);
        int deletedBlockCount = (deletedHash->packed_size + blockSize - 1) / blockSize;
        if(deletedBlockCount > blockCount) {
            deletedHash->offset += blockCount * blockSize;
            deletedHash->packed_size = deletedHash->file_size = (deletedBlockCount - blockCount) * blockSize;
        } else {
            lpk_release_deleted_hash(lpk, deletedHashIndex);
        }
        
        // copy
        lpk_copy_hash(lpk, dstHashIndex, patchHash, fileData, fileOffset);
    }
    
    // free
    free((void*)fileData);
    
    return blockCount;
}
    
int lpk_open_file(lpk_file* lpk, const char* filepath) {
    // result code
    int result = 0;
    
    // to avoid goto with do-while wrapper
    do {
        // try to open file
        if ((lpk->fp = fopen(filepath, "rb+")) == NULL) {
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
        
        // allocate memory for the hash table
        if((lpk->het = calloc(lpk->h.hash_table_count, sizeof(lpk_hash))) == NULL) {
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
    
    /* if no error was found, return zero. */
    return LPK_SUCCESS;
}
    
uint32_t lpk_get_file_hash_table_index(lpk_file* lpk, const char* filepath, uint16_t locale, LPKPlatform platform) {
    // get hash
    size_t pathLen = strlen(filepath);
    uint32_t hashI = hashlittle(filepath, pathLen, LPK_HASH_TAG_TABLE_INDEX) & (lpk->h.hash_table_count - 1);
    uint32_t hashA = hashlittle(filepath, pathLen, LPK_HASH_TAG_NAME_A);
    uint32_t hashB = hashlittle(filepath, pathLen, LPK_HASH_TAG_NAME_B);
    
    // find start entry
    lpk_hash* hash = lpk->het + hashI;
    while((hash->hash_a != hashA || hash->hash_b != hashB || hash->locale != locale || hash->platform != platform) && hash->next_hash != LPK_INDEX_INVALID) {
        hashI = hash->next_hash;
        hash = lpk->het + hashI;
    }
    
    // return
    if(hash->hash_a != hashA || hash->hash_b != hashB) {
        return LPK_INDEX_INVALID;
    } else {
        return hashI;
    }
}
    
uint32_t lpk_get_file_size(lpk_file* lpk, const char* filepath, uint16_t locale, LPKPlatform platform) {
    // find hash index
    uint32_t hashIndex = lpk_get_file_hash_table_index(lpk, filepath, locale, platform);
    if(hashIndex == LPK_INDEX_INVALID) {
        return 0;
    }
    
    // get block
    lpk_hash* hash = lpk->het + hashIndex;
    
    // return
    return hash->file_size;
}
    
uint8_t* lpk_extract_file(lpk_file* lpk, const char* filepath, uint32_t* size, const char* key, const uint32_t keyLen, uint16_t locale, LPKPlatform platform) {
    // init size
    if(size) {
        *size = 0;
    }
    
    // find hash index
    uint32_t hashIndex = lpk_get_file_hash_table_index(lpk, filepath, locale, platform);
    if(hashIndex == LPK_INDEX_INVALID) {
        return NULL;
    }
    
    // get hash
    lpk_hash* hash = lpk->het + hashIndex;
    
    // if not a used hash, return
    // if file is deleted, return
    if(!(hash->flags & LPK_FLAG_USED) || (hash->flags & LPK_FLAG_DELETED)) {
        return NULL;
    }
    
    // seek
    if(fseeko(lpk->fp, sizeof(lpk_header) + hash->offset, SEEK_SET) < 0) {
        return NULL;
    }
    
    // allocate memory
    uint32_t bufLen = hash->packed_size;
    uint8_t* buf = (uint8_t*)malloc(sizeof(uint8_t) * bufLen);
    
    // read, if failed, release buffer
    if(fread(buf, bufLen, 1, lpk->fp) != 1) {
        free(buf);
        buf = NULL;
    }
    
    // decrypt
    if(buf && hash->flags & LPK_FLAG_ENCRYPTED) {
        LPKEncryptAlgorithm encAlg = (hash->flags & LPK_MASK_ENCRYPTED) >> LPK_SHIFT_ENCRYPTED;
        uint8_t* out = NULL;;
        uint32_t outLen;
        if(s_dcyt_table[encAlg]) {
            if(s_dcyt_table[encAlg](buf, bufLen, (const uint8_t*)key, keyLen, &out, &outLen) == 0) {
                free(buf);
                buf = out;
                bufLen = outLen;
            } else {
                free(buf);
                buf = NULL;
            }
        }
    }
    
    // uncompress
    if(buf && hash->flags & LPK_FLAG_COMPRESSED) {
        LPKCompressAlgorithm cmpAlg = (hash->flags & LPK_MASK_COMPRESSED) >> LPK_SHIFT_COMPRESSED;
        uint8_t* out = NULL;
        uint32_t outLen;
        if(s_dcmp_table[cmpAlg]) {
            if(s_dcmp_table[cmpAlg](buf, bufLen, &out, &outLen) == 0) {
                free(buf);
                buf = out;
                bufLen = outLen;
            } else {
                free(buf);
                buf = NULL;
            }
        }
    }
    
    // ensure unpacked size is same as file size
    if(bufLen != hash->file_size) {
        free(buf);
        buf = NULL;
    }
    
    // save size
    if(size) {
        *size = hash->file_size;
    }
    
    // return
    return buf;
}
    
int lpk_get_used_hash_count(lpk_file* lpk) {
    int count = 0;
    lpk_hash* hash = lpk->het;
    for(int i = 0; i < lpk->h.hash_table_count; i++, hash++) {
        if(hash->flags & LPK_FLAG_USED) {
            count++;
        }
    }
    return count;
}
    
int lpk_apply_patch(lpk_file* lpk, lpk_file* patch) {
    // get used hash count in source and patch
    int srcHashCount = lpk_get_used_hash_count(lpk);
    int patchHashCount = lpk_get_used_hash_count(patch);
    
    // if total file count is larger than old hash entry count, enlarge hash
    // this is not very accurate but it is ok enough
    int approximateHashCount = srcHashCount + patchHashCount;
    if(approximateHashCount > lpk->h.hash_table_count) {
        // rebuild hash table
        uint32_t newCount = next_pot(approximateHashCount);
        lpk_rebuild_hash(lpk, newCount);
    }
    
    // new file start offset
    uint32_t oldHashTableOffset = lpk->h.hash_table_offset;
    uint32_t blockSize = 512 << lpk->h.block_size;
    
    // iterate hash in patch
    uint32_t freeHashIndex = 0;
    lpk_hash* patchHash = patch->het;
    for(int i = 0; i < patch->h.hash_table_count; i++, patchHash++) {
        // if hash is not used, skip
        if(!(patchHash->flags & LPK_FLAG_USED)) {
            continue;
        }
        
        // init hash found by patch hash
        uint32_t hashIndex = patchHash->hash_i & (lpk->h.hash_table_count - 1);
        lpk_hash* hash = lpk->het + hashIndex;
        
        // if patch hash is marked as deleted, delete hash and add it to deleted link
        // if hash is not used, it is a new file
        // if hash is used and it is head of link, append patch hash
        // if hash is used but not link head, move old hash
        if(patchHash->flags & LPK_FLAG_DELETED) {
            hashIndex = lpk_get_file_hash_table_index_by_hash(lpk, patchHash->hash_i, patchHash->hash_a, patchHash->hash_b, patchHash->locale, patchHash->platform);
            if(hashIndex != LPK_INDEX_INVALID) {
                uint32_t deletedHashIndex = lpk_delete_hash(lpk, hashIndex);
                lpk_link_deleted_hash(lpk, deletedHashIndex);
            }
        } else if(!(hash->flags & LPK_FLAG_USED)) {
            lpk_save_patch_file(lpk, patch, hashIndex, patchHash);
        } else if(hash->flags & LPK_FLAG_DELETED) {
            // next free hash index
            freeHashIndex = lpk_next_free_hash_index(lpk, freeHashIndex);
            
            // move old hash
            memcpy(lpk->het + freeHashIndex, hash, sizeof(lpk_hash));
            
            // fix link
            if(hash->prev_hash == LPK_INDEX_INVALID) {
                lpk->h.deleted_hash = freeHashIndex;
            } else {
                lpk->het[hash->prev_hash].next_hash = freeHashIndex;
            }
            if(hash->next_hash != LPK_INDEX_INVALID) {
                lpk->het[hash->next_hash].prev_hash = freeHashIndex;
            }
            
            // save patch file
            lpk_save_patch_file(lpk, patch, hashIndex, patchHash);
        } else if(hash->prev_hash == LPK_INDEX_INVALID) {
            // find by hash and locale and platform
            // if can't find, means it is a new file
            // if found, need compare size of old and new file, so there is more possibilities
            // if block count is same, just overwrite old file
            // if block count is not enough, need recycle old file and write new file in a new hash
            // if block count is more, need overwrite old file and record redundant blocks
            int blockCount = (patchHash->packed_size + blockSize - 1) / blockSize;
            uint32_t matchedHashIndex = lpk_get_file_hash_table_index_by_hash(lpk, patchHash->hash_i, patchHash->hash_a, patchHash->hash_b, patchHash->locale, patchHash->platform);
            if(matchedHashIndex == LPK_INDEX_INVALID) {
                // next free hash index
                freeHashIndex = lpk_next_free_hash_index(lpk, freeHashIndex);
                
                // save patch file
                lpk_save_patch_file(lpk, patch, freeHashIndex, patchHash);
                
                // link
                lpk->het[freeHashIndex].next_hash = hash->next_hash;
                lpk->het[freeHashIndex].prev_hash = hashIndex;
                if(hash->next_hash != LPK_INDEX_INVALID) {
                    lpk->het[hash->next_hash].prev_hash = freeHashIndex;
                }
                hash->next_hash = freeHashIndex;
            } else {
                hash = lpk->het + matchedHashIndex;
                int oldBlockCount = (hash->packed_size + blockSize - 1) / blockSize;
                if(oldBlockCount == blockCount) {
                    const uint8_t* fileData = lpk_get_file_packed_data(patch, patchHash);
                    if(fileData) {
                        uint32_t savedNextHash = hash->next_hash;
                        uint32_t savedPrevHash = hash->prev_hash;
                        lpk_copy_hash(lpk, matchedHashIndex, patchHash, fileData, hash->offset);
                        hash->next_hash = savedNextHash;
                        hash->prev_hash = savedPrevHash;
                        free((void*)fileData);
                    }
                } else if(oldBlockCount < blockCount) {
                    // block count is not enough, recycle this hash
                    uint32_t deletedHashIndex = lpk_delete_hash(lpk, matchedHashIndex);
                    lpk_link_deleted_hash(lpk, deletedHashIndex);
                    
                    // next free hash index
                    freeHashIndex = lpk_next_free_hash_index(lpk, freeHashIndex);
                    
                    // save patch file
                    lpk_save_patch_file(lpk, patch, freeHashIndex, patchHash);
                    
                    // link
                    lpk->het[freeHashIndex].next_hash = hash->next_hash;
                    lpk->het[freeHashIndex].prev_hash = hashIndex;
                    lpk->het[hash->next_hash].prev_hash = freeHashIndex;
                    hash->next_hash = freeHashIndex;
                } else {
                    const uint8_t* fileData = lpk_get_file_packed_data(patch, patchHash);
                    if(fileData) {
                        // copy in a free hash
                        freeHashIndex = lpk_next_free_hash_index(lpk, freeHashIndex);
                        lpk_copy_hash(lpk, freeHashIndex, patchHash, fileData, hash->offset);
                        free((void*)fileData);
                        
                        // link
                        lpk->het[freeHashIndex].prev_hash = hash->prev_hash;
                        lpk->het[freeHashIndex].next_hash = hash->next_hash;
                        
                        // increase matched hash offset
                        int blockCount = (patchHash->packed_size + blockSize - 1) / blockSize;
                        hash->offset += blockCount * blockSize;
                        hash->packed_size -= blockCount * blockSize;
                        hash->file_size = hash->packed_size;
                        
                        // move matched hash to deleted link
                        uint32_t deletedHashIndex = lpk_delete_hash(lpk, matchedHashIndex);
                        lpk_link_deleted_hash(lpk, deletedHashIndex);
                    }
                }
            }
        } else {
            // next free hash index
            freeHashIndex = lpk_next_free_hash_index(lpk, freeHashIndex);
            
            // move old hash
            memcpy(lpk->het + freeHashIndex, hash, sizeof(lpk_hash));
            
            // fix link
            lpk_hash* prev = lpk->het + hash->prev_hash;
            prev->next_hash = freeHashIndex;
            if(hash->next_hash != LPK_INDEX_INVALID) {
                lpk_hash* next = lpk->het + hash->next_hash;
                next->prev_hash = freeHashIndex;
            }
            
            // save file
            lpk_save_patch_file(lpk, patch, hashIndex, patchHash);
        }
    }
    
    // check offset is changed or not
    if(lpk->h.hash_table_offset != oldHashTableOffset) {
        lpk->h.archive_size = lpk->h.hash_table_offset - sizeof(lpk_header);
        
        // seek new hash table offset field
        if(fseeko(lpk->fp, sizeof(uint32_t) * 4, SEEK_SET) < 0) {
            return LPK_ERROR_SEEK;
        }
        
        // write new hash table offset
        if(fwrite(&lpk->h.hash_table_offset, sizeof(uint32_t), 1, lpk->fp) != 1) {
            return LPK_ERROR_WRITE;
        }
        
        // seek new archive size
        if(fseeko(lpk->fp, sizeof(uint32_t) * 2, SEEK_SET) < 0) {
            return LPK_ERROR_SEEK;
        }
        
        // write new archive size
        if(fwrite(&lpk->h.archive_size, sizeof(uint32_t), 1, lpk->fp) != 1) {
            return LPK_ERROR_WRITE;
        }
    }
    
    // seek new hash table count field
    if(fseeko(lpk->fp, sizeof(uint32_t) * 5, SEEK_SET) < 0) {
        return LPK_ERROR_SEEK;
    }
    
    // write new hash table count
    if(fwrite(&lpk->h.hash_table_count, sizeof(uint32_t), 1, lpk->fp) != 1) {
        return LPK_ERROR_WRITE;
    }
    
    // seek to start of hash table
    if(fseeko(lpk->fp, lpk->h.hash_table_offset, SEEK_SET) < 0) {
        return LPK_ERROR_SEEK;
    }
    
    // write hash table
    if(fwrite(lpk->het, sizeof(lpk_hash), lpk->h.hash_table_count, lpk->fp) != lpk->h.hash_table_count) {
        return LPK_ERROR_WRITE;
    }
    
    return LPK_SUCCESS;
}
    
void lpk_debug_output(lpk_file* lpk) {
#ifdef DEBUG_LPK
    // output head
    printf("hs: %u, as: %u, v: %u, bs: %u, h_off: %u, hc: %u, dh_h: %x\n\n",
           lpk->h.header_size,
           lpk->h.archive_size,
           lpk->h.version,
           512 << lpk->h.block_size,
           lpk->h.hash_table_offset,
           lpk->h.hash_table_count,
           lpk->h.deleted_hash);
    
    // output used hash
    lpk_hash* hash = lpk->het;
    for(int i = 0; i < lpk->h.hash_table_count; i++, hash++) {
        if((hash->flags & LPK_FLAG_USED) && !(hash->flags & LPK_FLAG_DELETED) && hash->prev_hash == LPK_INDEX_INVALID) {
            uint32_t hashIndex = i;
            int level = 0;
            while(hashIndex != LPK_INDEX_INVALID) {
                // indent arrow
                lpk_hash* link = lpk->het + hashIndex;
                for(int i = 0; i < level; i++) {
                    printf("--");
                }
                if(level > 0) {
                    printf(">");
                }
                
                // hash info
                printf("n: %s, s: %u, ps: %u, off: %lx, l: %x, p: %u\n",
                       link->filename,
                       link->file_size,
                       link->packed_size,
                       link->offset + sizeof(lpk_header),
                       link->locale,
                       link->platform);
                
                // increase level
                level++;
                hashIndex = link->next_hash;
            }
            printf("\n");
        }
    }
    printf("\n");
    
    // output free space
    {
        uint32_t blockSize = 512 << lpk->h.block_size;
        uint32_t hashIndex = lpk->h.deleted_hash;
        int level = 0;
        while(hashIndex != LPK_INDEX_INVALID) {
            // indent arrow
            lpk_hash* link = lpk->het + hashIndex;
            for(int i = 0; i < level; i++) {
                printf("--");
            }
            if(level > 0) {
                printf(">");
            }
            
            // hash info
            printf("free block: %u, off: %lx\n",
                   (link->packed_size + blockSize - 1) / blockSize,
                   link->offset + sizeof(lpk_header));
            
            // increase level
            level++;
            hashIndex = link->next_hash;
        }
    }
#else
    printf("you need compile lpk with macro DEBUG_LPK to make this method work");
#endif
}

#ifdef __cplusplus
}
#endif