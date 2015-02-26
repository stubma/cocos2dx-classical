//
//  TreeManager.m
//  lpk
//
//  Created by maruojie on 15/2/16.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "TreeManager.h"
#import "NSArray+Transform.h"
#import "ProgressViewController.h"
#import "NSMutableData+ReadWrite.h"
#import "NSData+Generator.h"
#import "NSData+Compression.h"
#import "NSData+Encryption.h"

@interface TreeManager ()

- (uint32_t)nextPOT:(uint32_t)x;
- (uint32_t)nextFreeHashIndex:(lpk_file*)f from:(uint32_t)from;
- (void)endProgressSheet:(ProgressViewController*)pvc;
- (void)outputExportedFileInfo;
- (int)writeOneFile:(LpkEntry*)e branch:(LpkBranchEntry*)b toHashIndex:(uint32_t)hashIndex blockIndex:(uint32_t)blockIndex ofLPK:(lpk_file*)lpk withFileHandler:(NSFileHandle*)fh atOffset:(uint32_t)offset;
- (NSString*)dynamicXORKeyForEntry:(LpkEntry*)e andBranch:(LpkBranchEntry*)b;
- (NSString*)dynamicTEAKeyForEntry:(LpkEntry*)e andBranch:(LpkBranchEntry*)b;
- (NSString*)dynamicXXTEAKeyForEntry:(LpkEntry*)e andBranch:(LpkBranchEntry*)b;

@end

@implementation TreeManager

- (id)init {
    if(self = [super init]) {
        self.root = [[LpkEntry alloc] init];
        self.exportPath = @"";
        self.projectPath = [@"~/Documents/Untitled.lpkproj" stringByExpandingTildeInPath];
        self.defaultCompressAlgorithm = LPKC_ZLIB;
        self.defaultEncryptAlgorithm = LPKE_NONE;
        self.autoSkipCompression = YES;
        self.blockSize = 0;
        self.xorStaticKey = @"";
        self.teaStaticKey = @"";
        self.xxteaStaticKey = @"";
        self.xorDynamicKey = NO;
        self.teaDynamicKey = NO;
        self.xxteaDynamicKey = NO;
        return self;
    }
    return nil;
}

- (void)addFiles:(NSArray*)paths toDir:(LpkEntry*)dir {
    // use root if dir is nil
    if(!dir) {
        dir = self.root;
    }
    
    // add every file, depends on it is folder or file
    for(NSString* path in paths) {
        LpkEntry* e = [[LpkEntry alloc] initWithPath:path];
        if(e) {
            // add to dir
            [dir addChild:e];
            
            // if it is dir also, add recursively
            if(e.isDir) {
                NSFileManager* fm = [NSFileManager defaultManager];
                NSArray* tmp = [fm contentsOfDirectoryAtPath:path error:nil];
                NSArray* subpaths = [tmp arrayByApplyingBlock:^id(id s) {
                    return [path stringByAppendingPathComponent:s];
                }];
                [self addFiles:subpaths toDir:e];
            }
        }
    }
    
    // sort
    [dir sortChildrenRecursively];
    
    // flag
    self.dirty = YES;
}

- (LpkEntry*)entryByKey:(NSString*)key {
    NSArray* parts = [key componentsSeparatedByString:@"/"];
    LpkEntry* e = self.root;
    for(NSString* name in parts) {
        if([@"" isEqualToString:name])
            continue;
        e = [e childByName:name];
        if(!e)
            break;
    }
    return e;
}

- (NSArray*)stripContainedKeys:(NSArray*)keys {
    // get folder entries
    NSArray* folders = [keys arrayByApplyingBlock:^id(id key) {
        LpkEntry* e = [self entryByKey:key];
        if(e && e.isDir) {
            return e;
        } else {
            return nil;
        }
    }];
    
    // remove file entries in folders
    return [keys arrayByApplyingBlock:^id(id key) {
        LpkEntry* e = [self entryByKey:key];
        if(e) {
            if(![e isContainedByAnyDir:folders]) {
                return e;
            }
        }
        
        return nil;
    }];
}

- (NSArray*)stripContainedEntries:(NSArray*)entries {
    // get folder entries
    NSArray* folders = [entries arrayByApplyingBlock:^id(id obj) {
        LpkEntry* e = (LpkEntry*)obj;
        if(e && e.isDir) {
            return e;
        } else {
            return nil;
        }
    }];
    
    // remove file entries in folders
    return [entries arrayByApplyingBlock:^id(id obj) {
        LpkEntry* e = (LpkEntry*)obj;
        if(e) {
            if(![e isContainedByAnyDir:folders]) {
                return e;
            }
        }
        
        return nil;
    }];
}

- (void)moveEntryByKeys:(NSArray*)keys toDir:(LpkEntry*)dir {
    // use root if dir is nil
    if(!dir) {
        dir = self.root;
    }
    
    // strip contained entries
    NSArray* ndupEntries = [self stripContainedKeys:keys];
    
    // move every entry
    NSMutableArray* affectedParents = [NSMutableArray array];
    for(LpkEntry* e in ndupEntries) {
        // detach entry from parent
        if(dir != e.parent && dir != e) {
            [affectedParents addObject:e.parent];
            [e removeFromParent];
            [dir addChild:e];
        }
    }
    
    // resort changed entry
    for(LpkEntry* e in affectedParents) {
        [e sortChildren];
    }
    
    // sort
    [dir sortChildren];
    
    // flag
    self.dirty = YES;
}

- (void)removeEntries:(NSArray*)entries {
    // strip contained entries
    NSArray* ndupEntries = [self stripContainedEntries:entries];
    
    // remove every entry
    for(LpkEntry* e in ndupEntries) {
        [e removeFromParent];
    }
    
    // flag
    self.dirty = YES;
}

- (void)removeEntry:(LpkEntry*)e {
    [e removeFromParent];
    self.dirty = YES;
}

- (void)removeBranch:(LpkBranchEntry*)b ofEntry:(LpkEntry*)e {
    [e.branches removeObject:b];
    self.dirty = YES;
}

- (void)newFolder:(NSString*)name toDir:(LpkEntry*)dir {
    // create entry
    LpkEntry* e = [[LpkEntry alloc] initWithFolderName:name];
    
    // use root if dir is nil
    if(!dir) {
        dir = self.root;
    }
    
    // add
    [dir addChild:e];
    
    // sort
    [dir sortChildren];
    
    // flag
    self.dirty = YES;
}

- (void)loadProject {
    NSDictionary* dict = [NSDictionary dictionaryWithContentsOfFile:self.projectPath];
    if(dict) {
        self.root = [LpkEntry decodeWithDictionary:dict];
        self.defaultCompressAlgorithm = (LPKCompressAlgorithm)[[dict objectForKey:@"d_cmp_alg"] intValue];
        self.defaultEncryptAlgorithm = (LPKEncryptAlgorithm)[[dict objectForKey:@"d_enc_alg"] intValue];
        self.autoSkipCompression = [[dict objectForKey:@"auto_skip_cmp"] boolValue];
        self.blockSize = [[dict objectForKey:@"block_size"] intValue];
        self.xorStaticKey = [dict objectForKey:@"xor_sk"];
        self.teaStaticKey = [dict objectForKey:@"tea_sk"];
        self.xxteaStaticKey = [dict objectForKey:@"xxtea_sk"];
        self.xorDynamicKey = [[dict objectForKey:@"xor_dk"] boolValue];
        self.teaDynamicKey = [[dict objectForKey:@"tea_dk"] boolValue];
        self.xxteaDynamicKey = [[dict objectForKey:@"xxtea_dk"] boolValue];
        if(!self.xorStaticKey) {
            self.xorStaticKey = @"";
        }
        if(!self.teaStaticKey) {
            self.teaStaticKey = @"";
        }
        if(!self.xxteaStaticKey) {
            self.xxteaStaticKey = @"";
        }
        
        // flag
        self.dirty = NO;
    }
}

- (void)saveProject {
    NSError* err = nil;
    NSOutputStream* os = [NSOutputStream outputStreamToFileAtPath:self.projectPath append:NO];
    [os open];
    NSMutableDictionary* root = [NSMutableDictionary dictionary];
    [self.root encodeWithDictionary:root relativeTo:[self.projectPath stringByDeletingLastPathComponent]];
    [root setObject:[NSNumber numberWithInt:self.defaultCompressAlgorithm] forKey:@"d_cmp_alg"];
    [root setObject:[NSNumber numberWithInt:self.defaultEncryptAlgorithm] forKey:@"d_enc_alg"];
    [root setObject:[NSNumber numberWithBool:self.autoSkipCompression] forKey:@"auto_skip_cmp"];
    [root setObject:[NSNumber numberWithInt:self.blockSize] forKey:@"block_size"];
    [root setObject:self.xorStaticKey forKey:@"xor_sk"];
    [root setObject:self.teaStaticKey forKey:@"tea_sk"];
    [root setObject:self.xxteaStaticKey forKey:@"xxtea_sk"];
    [root setObject:[NSNumber numberWithBool:self.xorDynamicKey] forKey:@"xor_dk"];
    [root setObject:[NSNumber numberWithBool:self.teaDynamicKey] forKey:@"tea_dk"];
    [root setObject:[NSNumber numberWithBool:self.xxteaDynamicKey] forKey:@"xxtea_dk"];
    if(![NSPropertyListSerialization writePropertyList:root
                                              toStream:os
                                                format:NSPropertyListXMLFormat_v1_0
                                               options:0
                                                 error:&err]) {
        NSAlert* alert = [[NSAlert alloc] init];
        [alert setMessageText:[err localizedDescription]];
        [alert beginSheetModalForWindow:[[NSApplication sharedApplication] mainWindow] completionHandler:nil];
    } else {
        self.dirty = NO;
    }
    [os close];
}

- (int)writeOneFile:(LpkEntry*)e branch:(LpkBranchEntry*)b toHashIndex:(uint32_t)hashIndex blockIndex:(uint32_t)blockIndex ofLPK:(lpk_file*)lpk withFileHandler:(NSFileHandle*)fh atOffset:(uint32_t)offset {
    // get key
    NSString* eKey = e.key;
    const void* key = (const void*)[eKey cStringUsingEncoding:NSUTF8StringEncoding];
    size_t len = [eKey lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    
    // get hash
    lpk_hash* hash = lpk->het + hashIndex;
    
    // fill hash
    hash->hash_a = hashlittle(key, len, LPK_HASH_TAG_NAME_A);
    hash->hash_b = hashlittle(key, len, LPK_HASH_TAG_NAME_B);
    hash->locale = b.locale;
    hash->platform = b.platform;
    hash->next_hash = LPK_HASH_FREE;
    hash->prev_hash = LPK_HASH_FREE;
    
    // resolve path
    NSString* path = b.realPath;
    if(![path isAbsolutePath]) {
        path = [[[self.projectPath stringByDeletingLastPathComponent] stringByAppendingPathComponent:path] stringByStandardizingPath];
    }
    
    // resolve compress and encrypt
    LPKCompressAlgorithm cmpAlg = b.compressAlgorithm == LPKC_DEFAULT ? self.defaultCompressAlgorithm : b.compressAlgorithm;
    LPKEncryptAlgorithm encAlg = b.encryptAlgorithm == LPKE_DEFAULT ? self.defaultEncryptAlgorithm : b.encryptAlgorithm;
    
    // get file data and compress it as needed
    uint32_t blockSize = 512 << lpk->h.block_size;
    NSData* data = [NSData dataWithContentsOfFile:path];
    NSData* cmpData = data;
    switch (cmpAlg) {
        case LPKC_ZLIB:
            cmpData = [data zlibDeflate];
            break;
        default:
            break;
    }
    uint32_t fileSize = (uint32_t)[data length];
    uint32_t compressSize = (uint32_t)[cmpData length];
    
    // if auto skip compression is set, cancel compression if compressed size is even larger than original size
    if(self.autoSkipCompression) {
        if(compressSize >= fileSize) {
            cmpData = data;
            compressSize = fileSize;
            cmpAlg = LPKC_NONE;
        }
    }
    
    // encrypt
    NSData* encData = cmpData;
    switch (encAlg) {
        case LPKE_XOR:
            if(self.xorDynamicKey) {
                encData = [cmpData xorData:[self dynamicXORKeyForEntry:e andBranch:b]];
            } else {
                encData = [cmpData xorData:self.xorStaticKey];
            }
            break;
        case LPKE_TEA:
            if(self.teaDynamicKey) {
                encData = [cmpData teaData:[self dynamicTEAKeyForEntry:e andBranch:b]];
            } else {
                encData = [cmpData teaData:self.teaStaticKey];
            }
            break;
        case LPKE_XXTEA:
            if(self.xxteaDynamicKey) {
                encData = [cmpData xxteaData:[self dynamicXXTEAKeyForEntry:e andBranch:b]];
            } else {
                encData = [cmpData xxteaData:self.xxteaStaticKey];
            }
            break;
        default:
            break;
    }
    uint32_t encSize = (uint32_t)[encData length];
    
    // write file and get block count
    [fh writeData:encData];
    uint32_t blockCount = (encSize + blockSize - 1) / blockSize;
    
    // fill junk to make it align with block size
    uint32_t junk = (blockSize - (encSize % blockSize)) % blockSize;
    if(junk > 0) {
        [fh writeData:[NSData dataWithByte:0 repeated:junk]];
    }
    
    // fill block struct
    lpk_block* block = lpk->bet + blockIndex;
    block->file_size = fileSize;
    block->packed_size = encSize;
    block->offset = offset;
    block->flags = LPK_FLAG_EXISTS;
    if(cmpAlg > LPKC_NONE) {
        block->flags |= LPK_FLAG_COMPRESSED;
        block->flags |= (cmpAlg << LPK_SHIFT_COMPRESSED);
    }
    if(encAlg > LPKE_NONE) {
        block->flags |= LPK_FLAG_ENCRYPTED;
        block->flags |= (encAlg << LPK_SHIFT_ENCRYPTED);
    }
    
    // save block index
    hash->block_table_index = blockIndex;
    
    // return block count
    return blockCount;
}

- (void)exportLPK:(ProgressViewController*)pvc {
    // ensure dest file is here
    NSFileManager* fm = [NSFileManager defaultManager];
    if(![fm fileExistsAtPath:self.exportPath]) {
        [fm createFileAtPath:self.exportPath contents:[NSData data] attributes:nil];
    } else {
        [fm removeItemAtPath:self.exportPath error:nil];
        [fm createFileAtPath:self.exportPath contents:[NSData data] attributes:nil];
    }
    NSFileHandle* fh = [NSFileHandle fileHandleForWritingAtPath:self.exportPath];
    NSMutableData* buf = [NSMutableData data];
    
    // get a list of all entries
    NSMutableArray* allFileEntries = [NSMutableArray array];
    [self.root collectFiles:allFileEntries];
    
    // progress hint
    pvc.progressIndicator.maxValue = [allFileEntries count] + 100;
    pvc.hintLabel.stringValue = @"Prepare for exporting...";
    
    // init part of file struct
    lpk_file lpk = { 0 };
    lpk.h.lpk_magic = LPK_MAGIC;
    lpk.h.header_size = sizeof(lpk_header);
    lpk.h.block_size = self.blockSize;
    lpk.files = [self.root getFileCountIncludeBranch];
    lpk.h.hash_table_count = [self nextPOT:lpk.files];
    lpk.h.block_table_count = [self nextPOT:lpk.files];
    lpk.het = (lpk_hash*)calloc(lpk.h.hash_table_count, sizeof(lpk_hash));
    lpk.bet = (lpk_block*)calloc(lpk.h.block_table_count, sizeof(lpk_block));
    for(int i = 0; i < lpk.h.hash_table_count; i++) {
        lpk.het[i].block_table_index = LPK_HASH_FREE;
        lpk.het[i].next_hash = LPK_HASH_FREE;
        lpk.het[i].prev_hash = LPK_HASH_FREE;
    }
    
    // progress hint
    [pvc.progressIndicator incrementBy:50];
    pvc.hintLabel.stringValue = @"Writting header...";
    
    do {
        // check abort
        if(pvc.abort)
            break;
        
        // write header
        [buf writeUInt32:lpk.h.lpk_magic];
        [buf writeUInt32:lpk.h.header_size];
        [buf writeUInt32:lpk.h.archive_size];
        [buf writeUInt16:lpk.h.version];
        [buf writeUInt16:lpk.h.block_size];
        [buf writeUInt32:lpk.h.hash_table_offset];
        [buf writeUInt32:lpk.h.block_table_offset];
        [buf writeUInt32:lpk.h.hash_table_count];
        [buf writeUInt32:lpk.h.block_table_count];
        [fh writeData:buf];
        [buf setLength:0];
        
        // start to write every file, but not include branch at first
        uint32_t totalSize = 0;
        uint32_t blockIndex = 0;
        uint32_t blockSize = 512 << lpk.h.block_size;
        uint32_t freeHashIndex = 0;
        for(LpkEntry* e in allFileEntries) {
            // get hash table index for this entry
            NSString* eKey = e.key;
            const void* key = (const void*)[eKey cStringUsingEncoding:NSUTF8StringEncoding];
            size_t len = [eKey lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
            uint32_t hashIndex = hashlittle(key, len, LPK_HASH_TAG_TABLE_INDEX) & (lpk.h.hash_table_count - 1);
            lpk_hash* hash = lpk.het + hashIndex;
            
            // progress hint
            [pvc.progressIndicator incrementBy:1];
            pvc.hintLabel.stringValue = [NSString stringWithFormat:@"Writting %@...", e.name];
            
            for(LpkBranchEntry* b in e.branches) {
                // check abort
                if(pvc.abort)
                    break;
                
                // block count of this file
                int blockCount = 0;
                
                // if it is free hash, just write it
                // if it is not free, but it is head of hash chain, just append it to link end in next free hash entry
                // if it is not free and not head of link, move current hash to next free index and put it here
                if(hash->block_table_index == LPK_HASH_FREE) {
                    blockCount = [self writeOneFile:e
                                             branch:b
                                        toHashIndex:hashIndex
                                         blockIndex:blockIndex
                                              ofLPK:&lpk
                                    withFileHandler:fh
                                           atOffset:totalSize];
                } else if(hash->prev_hash == LPK_HASH_FREE) {
                    // find tail
                    while(hash->next_hash != LPK_HASH_FREE) {
                        hash = lpk.het + hash->next_hash;
                        hashIndex = hash->next_hash;
                    }
                    
                    // find free entry
                    freeHashIndex = [self nextFreeHashIndex:&lpk from:freeHashIndex];
                    
                    // write file
                    blockCount = [self writeOneFile:e
                                             branch:b
                                        toHashIndex:freeHashIndex
                                         blockIndex:blockIndex
                                              ofLPK:&lpk
                                    withFileHandler:fh
                                           atOffset:totalSize];
                    
                    // link
                    lpk_hash* chainHash = lpk.het + freeHashIndex;
                    chainHash->prev_hash = hashIndex;
                    hash->next_hash = freeHashIndex;
                } else {
                    // find free entry
                    freeHashIndex = [self nextFreeHashIndex:&lpk from:freeHashIndex];
                    
                    // copy
                    memcpy(lpk.het + freeHashIndex, hash, sizeof(lpk_hash));
                    
                    // fix link
                    lpk_hash* prev = lpk.het + hash->prev_hash;
                    prev->next_hash = freeHashIndex;
                    if(hash->next_hash != LPK_HASH_FREE) {
                        lpk_hash* next = lpk.het + hash->next_hash;
                        next->prev_hash = freeHashIndex;
                    }
                    
                    // write file
                    blockCount = [self writeOneFile:e
                                             branch:b
                                        toHashIndex:hashIndex
                                         blockIndex:blockIndex
                                              ofLPK:&lpk
                                    withFileHandler:fh
                                           atOffset:totalSize];
                }
                
                // add total size
                totalSize += blockCount * blockSize;
                
                // move to next block
                blockIndex++;
            }
            
            // check abort
            if(pvc.abort)
                break;
        }
        
        // check abort
        if(pvc.abort)
            break;
        
        // progress hint
        [pvc.progressIndicator incrementBy:50];
        pvc.hintLabel.stringValue = @"Finalizing...";
        
        // write archive size
        lpk.h.archive_size = totalSize;
        [fh seekToFileOffset:sizeof(uint32_t) * 2];
        [buf writeUInt32:lpk.h.archive_size];
        [fh writeData:buf];
        [buf setLength:0];
        
        // write hash table offset
        lpk.h.hash_table_offset = lpk.h.archive_size + sizeof(lpk_header);
        [fh seekToFileOffset:sizeof(uint32_t) * 4];
        [buf writeUInt32:lpk.h.hash_table_offset];
        [fh writeData:buf];
        [buf setLength:0];
        
        // write block table offset
        lpk.h.block_table_offset = lpk.h.hash_table_offset + sizeof(lpk_hash) * lpk.h.hash_table_count;
        [buf writeUInt32:lpk.h.block_table_offset];
        [fh writeData:buf];
        [buf setLength:0];
        
        // write hash entry table
        [fh seekToEndOfFile];
        [buf appendBytes:lpk.het length:sizeof(lpk_hash) * lpk.h.hash_table_count];
        [fh writeData:buf];
        [buf setLength:0];
        
        // write block table
        [buf appendBytes:lpk.bet length:sizeof(lpk_block) * lpk.h.block_table_count];
        [fh writeData:buf];
        [buf setLength:0];
        
        // sync file
        [fh synchronizeFile];
        
        // progress
        [pvc.progressIndicator incrementBy:50];
        
        // check abort
        if(pvc.abort)
            break;
        
        // debug output
        [self outputExportedFileInfo];
    } while(false);
    
    // close file
    [fh closeFile];
    
    // release memory
    free(lpk.het);
    free(lpk.bet);
    
    // close progress
    [self performSelectorOnMainThread:@selector(endProgressSheet:) withObject:pvc waitUntilDone:NO];
}

- (void)endProgressSheet:(ProgressViewController*)pvc {
    [pvc.view.window.sheetParent endSheet:pvc.view.window returnCode:NSModalResponseOK];
}

- (uint32_t)nextFreeHashIndex:(lpk_file*)f from:(uint32_t)from {
    for(int i = from; i < f->h.hash_table_count; i++) {
        if(f->het[i].block_table_index == LPK_HASH_FREE) {
            return i;
        }
    }
    return LPK_HASH_FREE;
}

- (uint32_t)nextPOT:(uint32_t)x {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

- (void)rebuildFilterChildren:(NSString*)keyword {
    [self.root rebuildFilterChildren:keyword];
}

- (void)outputExportedFileInfo {
    // open file
    lpk_file lpk;
    int result = lpk_open_file(&lpk, [self.exportPath cStringUsingEncoding:NSUTF8StringEncoding]);
    if(result != 0) {
        NSLog(@"lpk_open_file, error: %d", result);
        return;
    }
    
    // output header
    NSLog(@"\nlpk file header:\n\tarchive size: %u\n\tblock size: %u\n\thash count: %u\n\tblock count: %u\n\thash offset: %u\n\tblock offset: %u",
          lpk.h.archive_size,
          512 << lpk.h.block_size,
          lpk.h.hash_table_count,
          lpk.h.block_table_count,
          lpk.h.hash_table_offset,
          lpk.h.block_table_offset);
    
    // extract a file
    uint32_t size;
    uint8_t* buf = lpk_extract_file(&lpk, "/Resources/res-iphone/manual/战场攻略_封印.jpg", &size, "战场攻略_封印.jpg", strlen("战场攻略_封印.jpg"), 0, LPKP_ANDROID);
    if(buf) {
        NSData* data = [NSData dataWithBytes:buf length:size];
        [data writeToFile:@"/Users/maruojie/Desktop/a.jpg" atomically:YES];
        free(buf);
    }
    
    // output every file info
//    NSMutableArray* allFileEntries = [NSMutableArray array];
//    [self.root collectFiles:allFileEntries];
//    for(LpkEntry* e in allFileEntries) {
//        // get file path as the key
//        const char* filepath = [e.key cStringUsingEncoding:NSUTF8StringEncoding];
//        
//        // get hash table index
//        uint32_t hashIndex = lpk_get_file_hash_table_index(&lpk, filepath, 0, LPKP_DEFAULT);
//        
//        // if invalid, print error
//        if(hashIndex == LPK_HASH_FREE) {
//            NSLog(@"\n%s\n\tERROR: can't find this file!!", filepath);
//            continue;
//        }
//        
//        // get block
//        lpk_hash* hash = lpk.het + hashIndex;
//        lpk_block* block = lpk.bet + hash->block_table_index;
//        
//        // print file info
//        NSString* locale = LOCALE_IDS[0];
//        if(hash->locale > 0) {
//            locale = [NSLocale localeIdentifierFromWindowsLocaleCode:hash->locale];
//        }
//        NSLog(@"\n%s\n\tfile size: %u\n\tpacked size: %u\n\toffset: %u\n\tlocale: %@\n\tplatform: %@\n\t",
//              filepath,
//              block->file_size,
//              block->packed_size,
//              block->offset,
//              locale,
//              PLATFORM_NAMES[hash->platform]);
//    }
    
    // close file
    result = lpk_close_file(&lpk);
    if(result != 0) {
        NSLog(@"lpk_close_file, error: %d", result);
        return;
    }
}

- (NSString*)dynamicXORKeyForEntry:(LpkEntry*)e andBranch:(LpkBranchEntry*)b {
    /*
     * If you set using dynamic key for TEA algorithm, you should implement this method
     * to return a proper key for one file. And in your game, you should implement it also
     * and feed it to lpk library
     */
    
    // for test, just use file name as the key
    return e.name;
}

- (NSString*)dynamicTEAKeyForEntry:(LpkEntry*)e andBranch:(LpkBranchEntry*)b {
    /*
     * If you set using dynamic key for TEA algorithm, you should implement this method
     * to return a proper key for one file. And in your game, you should implement it also
     * and feed it to lpk library
     */
    
    // for test, just use file name as the key
    return e.name;
}

- (NSString*)dynamicXXTEAKeyForEntry:(LpkEntry*)e andBranch:(LpkBranchEntry*)b {
    /*
     * If you set using dynamic key for XXTEA algorithm, you should implement this method
     * to return a proper key for one file. And in your game, you should implement it also
     * and feed it to lpk library
     */

    // for test, just use file name as the key
    return e.name;
}

@end
