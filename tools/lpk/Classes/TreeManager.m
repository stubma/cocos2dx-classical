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

@interface TreeManager ()

- (uint32_t)nextPOT:(uint32_t)x;
- (uint32_t)nextFreeHashIndex:(lpk_file*)f from:(uint32_t)from;
- (void)endProgressSheet:(ProgressViewController*)pvc;
- (void)outputExportedFileInfo;
- (int)writeOneFile:(LpkEntry*)e branch:(LpkBranchEntry*)b toHashIndex:(uint32_t)hashIndex blockIndex:(uint32_t)blockIndex ofLPK:(lpk_file*)lpk withFileHandler:(NSFileHandle*)fh atOffset:(uint32_t)offset;

@end

@implementation TreeManager

- (id)init {
    if(self = [super init]) {
        self.root = [[LpkEntry alloc] init];
        self.exportPath = @"";
        self.projectPath = [@"~/Documents/Untitled.lpkproj" stringByExpandingTildeInPath];
        self.defaultCompressAlgorithm = LPKC_ZLIB;
        self.defaultEncryptAlgorithm = LPKE_NONE;
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
    
    // resolve path
    NSString* path = b.realPath;
    if(![path isAbsolutePath]) {
        path = [[[self.projectPath stringByDeletingLastPathComponent] stringByAppendingPathComponent:path] stringByStandardizingPath];
    }
    
    // resolve compress and encrypt
    LPKCompressAlgorithm cmpAlg = b.compressAlgorithm == LPKC_DEFAULT ? self.defaultCompressAlgorithm : b.compressAlgorithm;
    LPKEncryptAlgorithm encAlg = b.encryptAlgorithm == LPKE_DEFAULT ? self.defaultEncryptAlgorithm : b.encryptAlgorithm;
    
    // write block
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
    [fh writeData:cmpData];
    uint32_t fileSize = (uint32_t)[data length];
    uint32_t compressSize = (uint32_t)[cmpData length];
    uint32_t blockCount = (compressSize + blockSize - 1) / blockSize;
    
    // fill junk to make it align with block size
    uint32_t junk = (blockSize - (compressSize % blockSize)) % blockSize;
    if(junk > 0) {
        [fh writeData:[NSData dataWithByte:0 repeated:junk]];
    }
    
    // fill block struct
    lpk_block* block = lpk->bet + blockIndex;
    block->file_size = fileSize;
    block->packed_size = compressSize;
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
    pvc.progressIndicator.maxValue = [allFileEntries count] * 2 + 100;
    pvc.hintLabel.stringValue = @"Prepare for exporting...";
    
    // init part of file struct
    lpk_file lpk = { 0 };
    lpk.h.lpk_magic = LPK_MAGIC;
    lpk.h.header_size = sizeof(lpk_header);
    lpk.h.block_size = 3;
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
    NSMutableArray* postponeFileEntries = [NSMutableArray array];
    for(LpkEntry* e in allFileEntries) {
        // get hash table index for this entry
        NSString* eKey = e.key;
        const void* key = (const void*)[eKey cStringUsingEncoding:NSUTF8StringEncoding];
        size_t len = [eKey lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
        uint32_t hashIndex = hashlittle(key, len, LPK_HASH_TAG_TABLE_INDEX) & (lpk.h.hash_table_count - 1);
        lpk_hash* hash = lpk.het + hashIndex;
        
        // if this entry is already used, postpone this entry
        if(hash->block_table_index != LPK_HASH_FREE) {
            [postponeFileEntries addObject:e];
            continue;
        }
        
        // progress hint
        [pvc.progressIndicator incrementBy:1];
        pvc.hintLabel.stringValue = [NSString stringWithFormat:@"Writting %@...", e.name];
        
        // write this file
        int blockCount = [self writeOneFile:e
                                     branch:[e getFirstBranch]
                                toHashIndex:hashIndex
                                 blockIndex:blockIndex
                                      ofLPK:&lpk
                            withFileHandler:fh
                                   atOffset:totalSize];
        
        // add total size
        totalSize += blockCount * blockSize;
        
        // move to next block
        blockIndex++;
    }
    
    // postpone entries
    uint32_t freeHashIndex = 0;
    for(LpkEntry* e in postponeFileEntries) {
        // progress hint
        [pvc.progressIndicator incrementBy:1];
        pvc.hintLabel.stringValue = [NSString stringWithFormat:@"Writting %@...", e.name];
        
        // get hash table index for this entry
        NSString* eKey = e.key;
        const void* key = (const void*)[eKey cStringUsingEncoding:NSUTF8StringEncoding];
        size_t len = [eKey lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
        uint32_t hashIndex = hashlittle(key, len, LPK_HASH_TAG_TABLE_INDEX) & (lpk.h.hash_table_count - 1);
        lpk_hash* hash = lpk.het + hashIndex;
        while(hash->next_hash != LPK_HASH_FREE) {
            hash = lpk.het + hash->next_hash;
        }
        
        // find a free hash slot
        freeHashIndex = [self nextFreeHashIndex:&lpk from:freeHashIndex];
        if(freeHashIndex == LPK_HASH_FREE) {
            NSLog(@"no free hash found! that should not be occured");
            break;
        }
        lpk_hash* chainHash = lpk.het + freeHashIndex;
        
        // write this file
        int blockCount = [self writeOneFile:e
                                     branch:[e getFirstBranch]
                                toHashIndex:freeHashIndex
                                 blockIndex:blockIndex
                                      ofLPK:&lpk
                            withFileHandler:fh
                                   atOffset:totalSize];
        
        // link hash
        hash->next_hash = freeHashIndex;
        chainHash->prev_hash = hashIndex;
        
        // add total size
        totalSize += blockCount * blockSize;
        
        // move to next block
        blockIndex++;
        
        // increase free index search start
        freeHashIndex++;
    }
    
    // process branch
    for(LpkEntry* e in allFileEntries) {
        // if only one branch, already processed, just skip
        [pvc.progressIndicator incrementBy:1];
        int bc = (int)[e.branches count];
        if(bc == 1) {
            continue;
        }
        
        // progress hint
        pvc.hintLabel.stringValue = [NSString stringWithFormat:@"Writting %@...", e.name];
        
        // iterate
        for(int i = 1; i < bc; i++) {
            // get hash table index for this entry
            NSString* eKey = e.key;
            const void* key = (const void*)[eKey cStringUsingEncoding:NSUTF8StringEncoding];
            size_t len = [eKey lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
            uint32_t hashIndex = hashlittle(key, len, LPK_HASH_TAG_TABLE_INDEX) & (lpk.h.hash_table_count - 1);
            lpk_hash* hash = lpk.het + hashIndex;
            while(hash->next_hash != LPK_HASH_FREE) {
                hash = lpk.het + hash->next_hash;
            }
            
            // find a free hash slot
            freeHashIndex = [self nextFreeHashIndex:&lpk from:freeHashIndex];
            if(freeHashIndex == LPK_HASH_FREE) {
                NSLog(@"no free hash found! that should not be occured");
                break;
            }
            lpk_hash* chainHash = lpk.het + freeHashIndex;
            
            // write this file
            int blockCount = [self writeOneFile:e
                                         branch:[e.branches objectAtIndex:i]
                                    toHashIndex:freeHashIndex
                                     blockIndex:blockIndex
                                          ofLPK:&lpk
                                withFileHandler:fh
                                       atOffset:totalSize];
            
            // link hash
            hash->next_hash = freeHashIndex;
            chainHash->prev_hash = hashIndex;
            
            // add total size
            totalSize += blockCount * blockSize;
            
            // move to next block
            blockIndex++;
            
            // increase free index search start
            freeHashIndex++;
        }
    }
    
    // progress hint
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
    
    // close file
    [fh synchronizeFile];
    [fh closeFile];
    
    // release memory
    free(lpk.het);
    free(lpk.bet);
    
    // progress
    [pvc.progressIndicator incrementBy:50];
    
    // debug output
    [self outputExportedFileInfo];
    
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
    uint8_t* buf = lpk_extract_file(&lpk, "/Resources/res-iphone/manual/战场攻略_封印.jpg", &size);
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
//        uint32_t hashIndex = lpk_get_file_hash_table_index(&lpk, filepath);
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

@end
