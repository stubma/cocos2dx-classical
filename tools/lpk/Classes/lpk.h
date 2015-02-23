//
//  lpk.h
//  lpk
//
//  Created by maruojie on 15/2/15.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#ifndef __lpk__lpk__
#define __lpk__lpk__

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * define generic lpk archive information. 
 * lpk archive header ('LPK\x1A')
 */
#define LPK_MAGIC 0x1A4B504C

// Hash table entry is not used
#define LPK_HASH_FREE 0xFFFFFFFF
    
// hash initial
#define LPK_HASH_TAG_TABLE_INDEX 0
#define LPK_HASH_TAG_NAME_A 0x100
#define LPK_HASH_TAG_NAME_B 0x200
    
/* define values used by flags. */
#define LPK_FLAG_EXISTS			0x80000000	/* set if file exists, reset when the file was deleted. */
#define LPK_FLAG_ENCRYPTED		0x00000001	/* indicates whether file is encrypted. */
#define LPK_FLAG_COMPRESSED		0x00000002	/* file is compressed. */
#define LPK_FLAG_CRC			0x40000000	/* compressed block offset table has CRC checksum. */
    
typedef enum {
    LPKC_NONE
} LPKCompressAlgorithm;
    
typedef enum {
    LPKE_NONE
} LPKEncryptAlgorithm;
    
typedef enum {
    LPKP_DEFAULT,
    LPKP_IOS,
    LPKP_ANDROID
} LPKPlatform;
    
/* lpk archive header. */
typedef struct {
    uint32_t lpk_magic;         /* the 0x1A4B504C ('LPK\x1A') signature. */
    uint32_t header_size;		/* lpk archive header size. */
    uint32_t archive_size;		/* size of lpk archive. */
    uint16_t version;           /* 0000, start from zero */
    uint16_t block_size;		/* size of file block is (512 * 2 ^ block size). */
    uint32_t hash_table_offset;	/* file position of lpk_hash. */
    uint32_t block_table_offset;/* file position of lpk_block, each entry has 16 bytes. */
    uint32_t hash_table_count;	/* number of entries in hash table. */
    uint32_t block_table_count;	/* number of entries in the block table. */
} lpk_header;

/* hash entry, all files in the archive are searched by their hashes. */
typedef struct {
    uint32_t hash_a;			/* the first two uint32_ts are the encrypted file. */
    uint32_t hash_b;			/* the first two uint32_ts are the encrypted file. */
    uint16_t locale;			/* locale information, in Windows LCID. */
    uint16_t platform;          /* platform information and zero is default. */
    
    /* 
     * index to file description block
     * this entry is not used if it is LPK_HASH_FREE
     */
    uint32_t block_table_index;
    
    /*
     * next hash to the file with same name but different locale and platform, 
     * no next if it is LPK_HASH_FREE
     */
    uint32_t next_hash;
    
    /*
     * previous hash to the file with same name but different locale and platform,
     * no previous if it is LPK_HASH_FREE
     */
    uint32_t prev_hash;
} lpk_hash;

/* file description block contains informations about the file. */
typedef struct {
    uint32_t offset;			/* block file starting position in the archive. */
    uint32_t packed_size;		/* file size after processed, i.e., compress, or encrypt, or both). */
    uint32_t file_size;         /* file size. */
    uint32_t flags;             /* flags. */
} lpk_block;
    
typedef struct {
    lpk_header h; // header
    lpk_hash* het; // hash entry table
    lpk_block* bet; // block entry table
    uint32_t files; // file count
} lpk_file;

#ifdef __cplusplus
}
#endif
    
#endif /* defined(__lpk__lpk__) */
