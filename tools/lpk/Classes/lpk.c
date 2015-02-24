//
//  lpk.c
//  lpk
//
//  Created by maruojie on 15/2/15.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#include "lpk.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
int lpk_open_file(const char* filepath, lpk_file* lpk) {
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
        if(fread(&lpk->h, 1, sizeof(lpk_header), lpk->fp) != sizeof(lpk_header)) {
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
        if(fread(lpk->het, 1, lpk->h.hash_table_count * sizeof(lpk_hash), lpk->fp) != lpk->h.hash_table_count * sizeof(lpk_hash)) {
            result = LPK_ERROR_READ;
            break;
        }
        
        // seek to block table
        if(fseeko(lpk->fp, lpk->h.block_table_offset, SEEK_SET) < 0) {
            result = LPK_ERROR_SEEK;
            break;
        }
        
        // read block table into buffer
        if(fread(lpk->bet, 1, lpk->h.block_table_count * sizeof(lpk_block), lpk->fp) != lpk->h.block_table_count * sizeof(lpk_block)) {
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
    
#ifdef __cplusplus
}
#endif