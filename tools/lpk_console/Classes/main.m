/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-classical
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#import <Foundation/Foundation.h>
#import <getopt.h>
#import "support/res/lpk.h"
#import "LpkEntry.h"
#import "LpkBranchEntry.h"
#import "NSArray+Transform.h"
#import "NSMutableData+ReadWrite.h"
#import "NSData+Compression.h"
#import "NSData+Encryption.h"
#import "NSData+Generator.h"
#import "hash_bob_jenkins_v2.h"
#import "tea.h"
#import "xxtea.h"

static NSString* s_root = NULL;
static NSString* s_staticKey = NULL;
static BOOL s_dynamicKey = NO;

static uint32_t nextPOT(uint32_t x) {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

static uint32_t nextFreeHashIndex(lpk_file* f, uint32_t from) {
    for(int i = from; i < f->h.hash_table_count; i++) {
        if(!(f->het[i].flags & LPK_FLAG_USED)) {
            return i;
        }
    }
    return LPK_INDEX_INVALID;
}

static NSString* dynamicKeyFor(LpkEntry* e, LpkBranchEntry* b) {
    return e.name;
}

static void usage() {
    NSLog(@"\nlpk command line tool usage:\n"
          "lpk [command] [options]\n\n"
          "command available:\n"
          "* help: show help of one command\n"
          "* make: create lpk archive from a root folder\n"
          "\t--root [path]: specify root folder of files to be packed\n"
          "\t--out [path]: the path of generated lpk archive, if not set, it will be generated at current\n"
          "\t\tdirectory with a default name\n"
          "\t--block [num]: set block size, the block size equals 512 << [num]\n"
          "\t--compress [none|zip]: set default compress algorithm for archive files, by default it is zip\n"
          "\t--encrypt [none|tea|xxtea|xor]: set default encrypt algorithm for files, by default it is none\n"
          "\t--static [key]: set static key for encryption\n"
          "\t--dynamic: set use dynamic key for encryption, currently the key is file name\n"
          "* extract: extract folder or file from lpk archive\n"
          "\t--path [path]: file path relative to archive root, such as /folder/a.txt\n"
          "\t--out [path]: path to save extracted file, if not set, will be saved at current directory\n"
          "\t--locale [locale identifier]: locale identifier in ISO 639-1, if not set, default will be used\n"
          "\t--platform [iOS|Android]: platform, if not set, default will be used\n"
          "\t--static [key]: set static key for decryption\n"
          "\t--dynamic: set use dynamic key for decryption, currently the key is file name\n"
          "\t[lpk]: lpk archive path\n"
          "* patch: patch a lpk archive with a patch lpk\n"
          "\t--to [path]: destination lpk archive to be patched\n"
          "\t--from [path]: patch lpk file\n"
          "\t--nobak: if set, destination lpk archive will not be backuped\n"
          "* dump: dump info of a lpk archive, such as file list, avaiable space\n"
          "\t[lpk]: specify lpk archive you want to dump\n");
}

static void addFiles(NSArray* paths, LpkEntry* dir) {
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
                addFiles(subpaths, e);
            }
        }
    }
}

static int writeOneFile(LpkEntry* e, LpkBranchEntry* b, uint32_t hashIndex, lpk_file* lpk, NSFileHandle* fh, uint32_t offset) {
    // default
    LPKCompressAlgorithm defaultCompressAlgorithm = LPKC_ZLIB;
    LPKEncryptAlgorithm defaultEncryptAlgorithm = LPKE_NONE;
    BOOL autoSkipCompression = YES;
    
    // get key
    NSString* eKey = e.key;
    const void* key = (const void*)[eKey cStringUsingEncoding:NSUTF8StringEncoding];
    size_t len = [eKey lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    
    // get hash
    lpk_hash* hash = lpk->het + hashIndex;
    
    // fill hash
#ifdef DEBUG_LPK
    sprintf(hash->filename, "%s", key);
#endif
    hash->hash_i = hashlittle(key, len, LPK_HASH_TAG_TABLE_INDEX);
    hash->hash_a = hashlittle(key, len, LPK_HASH_TAG_NAME_A);
    hash->hash_b = hashlittle(key, len, LPK_HASH_TAG_NAME_B);
    hash->locale = b.locale;
    hash->platform = b.platform;
    hash->next_hash = LPK_INDEX_INVALID;
    hash->prev_hash = LPK_INDEX_INVALID;
    
    // other info of file
    uint32_t blockCount = 0;
    uint32_t fileSize = 0;
    uint32_t encSize = 0;
    LPKCompressAlgorithm cmpAlg = LPKC_NONE;
    LPKEncryptAlgorithm encAlg = LPKE_NONE;
    
    // if entry is not deleted, write file
    if(!b.markAsDeleted) {
        // resolve path
        NSString* path = b.realPath;
        if(![path isAbsolutePath]) {
            path = [[[s_root stringByDeletingLastPathComponent] stringByAppendingPathComponent:path] stringByStandardizingPath];
        }
        
        // resolve compress and encrypt
        cmpAlg = b.compressAlgorithm == LPKC_DEFAULT ? defaultCompressAlgorithm : b.compressAlgorithm;
        encAlg = b.encryptAlgorithm == LPKE_DEFAULT ? defaultEncryptAlgorithm : b.encryptAlgorithm;
        
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
        fileSize = (uint32_t)[data length];
        uint32_t compressSize = (uint32_t)[cmpData length];
        
        // if auto skip compression is set, cancel compression if compressed size is even larger than original size
        if(autoSkipCompression) {
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
                if(s_dynamicKey) {
                    encData = [cmpData xorData:dynamicKeyFor(e, b)];
                } else {
                    encData = [cmpData xorData:s_staticKey];
                }
                break;
            case LPKE_TEA:
                if(s_dynamicKey) {
                    encData = [cmpData teaData:dynamicKeyFor(e, b)];
                } else {
                    encData = [cmpData teaData:s_staticKey];
                }
                break;
            case LPKE_XXTEA:
                if(s_dynamicKey) {
                    encData = [cmpData xxteaData:dynamicKeyFor(e, b)];
                } else {
                    encData = [cmpData xxteaData:s_staticKey];
                }
                break;
            default:
                break;
        }
        encSize = (uint32_t)[encData length];
        
        // write file and get block count
        [fh writeData:encData];
        blockCount = (encSize + blockSize - 1) / blockSize;
        
        // fill junk to make it align with block size
        uint32_t junk = (blockSize - (encSize % blockSize)) % blockSize;
        if(junk > 0) {
            [fh writeData:[NSData dataWithByte:0 repeated:junk]];
        }
    }
    
    // fill other hash info
    hash->file_size = fileSize;
    hash->packed_size = encSize;
    hash->offset = offset;
    hash->flags = LPK_FLAG_USED;
    if(b.markAsDeleted) {
        hash->flags |= LPK_FLAG_DELETED;
    }
    if(cmpAlg > LPKC_NONE) {
        hash->flags |= LPK_FLAG_COMPRESSED;
        hash->flags |= (cmpAlg << LPK_SHIFT_COMPRESSED);
    }
    if(encAlg > LPKE_NONE) {
        hash->flags |= LPK_FLAG_ENCRYPTED;
        hash->flags |= (encAlg << LPK_SHIFT_ENCRYPTED);
    }
    
    // return block count
    return blockCount;
}

static void make(NSString* root, NSString* dst, int blockSize, NSString* cmp, NSString* enc) {
    // validate arguments
    if(dst == nil) {
        dst = @"./out.lpk";
    }
    if(![@"none" isEqualToString:enc] && ![@"tea" isEqualToString:enc] && ![@"xxtea" isEqualToString:enc] && ![@"xor" isEqualToString:cmp]) {
        enc = @"none";
    }
    if(![enc isEqualToString:@"none"] && !s_dynamicKey && !s_staticKey) {
        enc = @"none";
    }
    if(![@"none" isEqualToString:cmp] && ![@"zip" isEqualToString:cmp]) {
        cmp = @"zip";
    }
    
    // normalize path
    root = [[root stringByExpandingTildeInPath] stringByStandardizingPath];
    dst = [[dst stringByExpandingTildeInPath] stringByStandardizingPath];
    s_root = root;
    
    // new root
    LpkEntry* rootEntry = [[LpkEntry alloc] init];
    
    // subpaths under root
    NSFileManager* fm = [NSFileManager defaultManager];
    NSArray* tmp = [fm contentsOfDirectoryAtPath:root error:nil];
    NSArray* subpaths = [tmp arrayByApplyingBlock:^id(id s) {
        return [root stringByAppendingPathComponent:s];
    }];
    
    // add to root
    addFiles(subpaths, rootEntry);
    
    // sort
    [rootEntry sortChildrenRecursively];
    
    // ensure dest file is here
    if(![fm fileExistsAtPath:dst]) {
        [fm createFileAtPath:dst contents:[NSData data] attributes:nil];
    } else {
        [fm removeItemAtPath:dst error:nil];
        [fm createFileAtPath:dst contents:[NSData data] attributes:nil];
    }
    NSFileHandle* fh = [NSFileHandle fileHandleForWritingAtPath:dst];
    NSMutableData* buf = [NSMutableData data];
    
    // get a list of all entries
    NSMutableArray* allFileEntries = [NSMutableArray array];
    [rootEntry collectFiles:allFileEntries];
    
    // progress hint
    NSLog(@"Prepare for exporting...");
    
    // init part of file struct
    lpk_file lpk = { 0 };
    lpk.h.lpk_magic = LPK_MAGIC;
    lpk.h.header_size = sizeof(lpk_header);
    lpk.h.block_size = blockSize;
    lpk.h.deleted_hash = LPK_INDEX_INVALID;
    lpk.files = [rootEntry getFileCountIncludeBranch];
    lpk.h.hash_table_count = nextPOT(lpk.files);
    lpk.het = (lpk_hash*)calloc(lpk.h.hash_table_count, sizeof(lpk_hash));
    for(int i = 0; i < lpk.h.hash_table_count; i++) {
        lpk.het[i].next_hash = LPK_INDEX_INVALID;
        lpk.het[i].prev_hash = LPK_INDEX_INVALID;
    }
    
    // progress hint
    NSLog(@"Writting header...");
    
    do {
        // write header
        [buf writeUInt32:lpk.h.lpk_magic];
        [buf writeUInt32:lpk.h.header_size];
        [buf writeUInt32:lpk.h.archive_size];
        [buf writeUInt16:lpk.h.version];
        [buf writeUInt16:lpk.h.block_size];
        [buf writeUInt32:lpk.h.hash_table_offset];
        [buf writeUInt32:lpk.h.hash_table_count];
        [buf writeUInt32:lpk.h.deleted_hash];
        [fh writeData:buf];
        [buf setLength:0];
        
        // start to write every file, but not include branch at first
        uint32_t totalSize = 0;
        uint32_t freeHashIndex = 0;
        for(LpkEntry* e in allFileEntries) {
            // get hash table index for this entry
            NSString* eKey = e.key;
            const void* key = (const void*)[eKey cStringUsingEncoding:NSUTF8StringEncoding];
            size_t len = [eKey lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
            uint32_t hashIndex = hashlittle(key, len, LPK_HASH_TAG_TABLE_INDEX) & (lpk.h.hash_table_count - 1);
            lpk_hash* hash = lpk.het + hashIndex;
            uint32_t hashIndexBak = hashIndex;
            lpk_hash* hashbak = hash;
            
            // progress hint
            NSLog(@"Writting %@...", e.name);
            
            for(LpkBranchEntry* b in e.branches) {
                // block count of this file
                int blockCount = 0;
                hash = hashbak;
                hashIndex = hashIndexBak;
                
                // if branch is marked as deleted, save it in a free hash and add to deleted link
                // if it is free hash, just write it
                // if it is not free, but it is head of hash chain, just append it to link end in next free hash entry
                // if it is not free and not head of link, move current hash to next free index and put it here
                // if it is not free and it is a deleted hash, move it
                if(b.markAsDeleted) {
                    // find free entry
                    freeHashIndex = nextFreeHashIndex(&lpk, freeHashIndex);
                    
                    // write file
                    blockCount = writeOneFile(e, b, freeHashIndex, &lpk, fh, totalSize);
                    
                    // link
                    if(lpk.h.deleted_hash == LPK_INDEX_INVALID) {
                        lpk.h.deleted_hash = freeHashIndex;
                    } else {
                        hash = lpk.het + freeHashIndex;
                        lpk_hash* deleted_head = lpk.het + lpk.h.deleted_hash;
                        hash->next_hash = lpk.h.deleted_hash;
                        deleted_head->prev_hash = freeHashIndex;
                        lpk.h.deleted_hash = freeHashIndex;
                    }
                } else if(!(hash->flags & LPK_FLAG_USED)) {
                    blockCount = writeOneFile(e, b, hashIndex, &lpk, fh, totalSize);
                } else if(hash->flags & LPK_FLAG_DELETED) {
                    // find free entry
                    freeHashIndex = nextFreeHashIndex(&lpk, freeHashIndex);
                    
                    // copy
                    memcpy(lpk.het + freeHashIndex, hash, sizeof(lpk_hash));
                    
                    // fix link
                    if(hash->prev_hash == LPK_INDEX_INVALID) {
                        lpk.h.deleted_hash = freeHashIndex;
                    } else {
                        lpk_hash* prev = lpk.het + hash->prev_hash;
                        prev->next_hash = freeHashIndex;
                    }
                    if(hash->next_hash != LPK_INDEX_INVALID) {
                        lpk_hash* next = lpk.het + hash->next_hash;
                        next->prev_hash = freeHashIndex;
                    }
                    
                    // write file
                    blockCount = writeOneFile(e, b, hashIndex, &lpk, fh, totalSize);
                } else if(hash->prev_hash == LPK_INDEX_INVALID) {
                    // find tail
                    while(hash->next_hash != LPK_INDEX_INVALID) {
                        hashIndex = hash->next_hash;
                        hash = lpk.het + hash->next_hash;
                    }
                    
                    // find free entry
                    freeHashIndex = nextFreeHashIndex(&lpk, freeHashIndex);
                    
                    // write file
                    blockCount = writeOneFile(e, b, freeHashIndex, &lpk, fh, totalSize);
                    
                    // link
                    lpk_hash* chainHash = lpk.het + freeHashIndex;
                    chainHash->prev_hash = hashIndex;
                    hash->next_hash = freeHashIndex;
                } else {
                    // find free entry
                    freeHashIndex = nextFreeHashIndex(&lpk, freeHashIndex);
                    
                    // copy
                    memcpy(lpk.het + freeHashIndex, hash, sizeof(lpk_hash));
                    
                    // fix link
                    lpk_hash* prev = lpk.het + hash->prev_hash;
                    prev->next_hash = freeHashIndex;
                    if(hash->next_hash != LPK_INDEX_INVALID) {
                        lpk_hash* next = lpk.het + hash->next_hash;
                        next->prev_hash = freeHashIndex;
                    }
                    
                    // write file
                    blockCount = writeOneFile(e, b, hashIndex, &lpk, fh, totalSize);
                }
                
                // add total size
                totalSize += blockCount * (512 << blockSize);
            }
        }
        
        // progress hint
        NSLog(@"Finalizing...");
        
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
        
        // write hash entry table
        [fh seekToEndOfFile];
        [buf appendBytes:lpk.het length:sizeof(lpk_hash) * lpk.h.hash_table_count];
        [fh writeData:buf];
        [buf setLength:0];
        
        // write deleted hash head
        [fh seekToFileOffset:sizeof(uint32_t) * 6];
        [buf writeUInt32:lpk.h.deleted_hash];
        [fh writeData:buf];
        [buf setLength:0];
        
        // sync file
        [fh synchronizeFile];
        
        // progress hint
        NSLog(@"done");
    } while(false);
    
    // close file
    [fh closeFile];
    
    // release memory
    free(lpk.het);
}

static void extract(NSString* archive, NSString* key, NSString* dstDir, uint32_t lcid, LPKPlatform platform) {
    // validate
    if(!key) {
        NSLog(@"please specify file path you want to extract");
        return;
    }
    if(!dstDir) {
        dstDir = @".";
    }
    
    // normalize path
    dstDir = [[dstDir stringByExpandingTildeInPath] stringByStandardizingPath];
    archive = [[archive stringByExpandingTildeInPath] stringByStandardizingPath];
    
    // validate archive existence
    NSFileManager* fm = [NSFileManager defaultManager];
    if(![fm fileExistsAtPath:archive]) {
        NSLog(@"lpk archive doesn't not exist");
        return;
    }
    
    // open archive
    lpk_file lpk;
    int result = lpk_open_file(&lpk, [archive cStringUsingEncoding:NSUTF8StringEncoding]);
    if(result != 0) {
        NSLog(@"lpk_open_file, open source error: %d", result);
        return;
    }
    
    // extract
    uint32_t size;
    uint8_t* buf = lpk_extract_file(&lpk,
                                    [key cStringUsingEncoding:NSUTF8StringEncoding],
                                    &size,
                                    [s_staticKey cStringUsingEncoding:NSUTF8StringEncoding],
                                    (uint32_t)[s_staticKey lengthOfBytesUsingEncoding:NSUTF8StringEncoding],
                                    lcid,
                                    platform);
    if(buf) {
        NSData* data = [NSData dataWithBytes:buf length:size];
        [data writeToFile:[dstDir stringByAppendingPathComponent:[key lastPathComponent]] atomically:YES];
        free(buf);
        NSLog(@"extract done");
    } else {
        NSLog(@"extract failed");
    }
    
    // close lpk
    lpk_close_file(&lpk);
}

static void patch(NSString* to, NSString* from, BOOL noBackup) {
    NSLog(@"patch %@, %@, %d", to, from, noBackup);
}

static void dump(NSString* archive) {
    // normalize path
    archive = [[archive stringByExpandingTildeInPath] stringByStandardizingPath];
    
    // check existence
    NSFileManager* fm = [NSFileManager defaultManager];
    if(![fm fileExistsAtPath:archive]) {
        NSLog(@"lpk archive doesn't exist");
        return;
    }
    
    // open
    lpk_file lpk;
    int result = lpk_open_file(&lpk, [archive cStringUsingEncoding:NSUTF8StringEncoding]);
    if(result != 0) {
        NSLog(@"lpk_open_file, error: %d", result);
        return;
    }
    
    // debug output
    lpk_debug_output(&lpk);
    
    // close file
    result = lpk_close_file(&lpk);
    if(result != 0) {
        NSLog(@"lpk_close_file, error: %d", result);
        return;
    }
}

int main(int argc, const char * argv[]) {
    int ret = 0;
    @autoreleasepool {
        do {
            // at least two arguments
            if(argc < 2) {
                usage();
                break;
            }
            
            // check command
            NSString* cmd = [NSString stringWithUTF8String:argv[1]];
            if([@"help" isEqualToString:cmd]) {
                usage();
                break;
            } else if([@"make" isEqualToString:cmd]) {
                // parse arguments for make command
                NSString* root = nil;
                NSString* dst = nil;
                NSString* cmp = @"zip";
                NSString* enc = @"none";
                NSString* staticKey = nil;
                int blockSize = 0;
                BOOL dynamicKey = NO;
                int opt;
                const char* short_opts = "r:o:c:e:s:d";
                static struct option long_options[] = {
                    { "root", required_argument, NULL, 'r' },
                    { "out", required_argument, NULL, 'o' },
                    { "block", required_argument, NULL, 'b' },
                    { "compress", required_argument, NULL, 'c' },
                    { "encrypt", required_argument, NULL, 'e' },
                    { "static", required_argument, NULL, 's' },
                    { "dynamic", no_argument, NULL, 'd' }
                };
                while((opt = getopt_long(argc, argv, short_opts, long_options, NULL)) != -1) {
                    switch (opt) {
                        case 'r':
                            root = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'o':
                            dst = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'b':
                            blockSize = atoi(optarg);
                            break;
                        case 'c':
                            cmp = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'e':
                            enc = [NSString stringWithUTF8String:optarg];
                            break;
                        case 's':
                            staticKey = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'd':
                            dynamicKey = YES;
                            break;
                        default:
                            break;
                    }
                }
                
                // do make
                s_root = root;
                s_staticKey = staticKey;
                s_dynamicKey = dynamicKey;
                make(root, dst, blockSize, cmp, enc);
            } else if([@"extract" isEqualToString:cmd]) {
                NSString* archive = nil;
                NSString* dst = nil;
                NSString* path = nil;
                NSString* staticKey = @"";
                uint32_t lcid = 0;
                LPKPlatform platform = LPKP_DEFAULT;
                BOOL dynamicKey = NO;
                int opt;
                const char* short_opts = "p:o:";
                static struct option long_options[] = {
                    { "path", required_argument, NULL, 'p' },
                    { "out", required_argument, NULL, 'o' },
                    { "locale", required_argument, NULL, 'l' },
                    { "platform", required_argument, NULL, 't' },
                    { "static", required_argument, NULL, 's' },
                    { "dynamic", no_argument, NULL, 'd' }
                };
                while((opt = getopt_long(argc, argv, short_opts, long_options, NULL)) != -1) {
                    switch (opt) {
                        case 'p':
                            path = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'o':
                            dst = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'l':
                            lcid = [NSLocale windowsLocaleCodeFromLocaleIdentifier:[NSString stringWithUTF8String:optarg]];
                            break;
                        case 't':
                        {
                            NSString* pft = [NSString stringWithUTF8String:optarg];
                            if([@"iOS" compare:pft options:NSCaseInsensitiveSearch] == NSOrderedSame) {
                                platform = LPKP_IOS;
                            } else if([@"Android" compare:pft options:NSCaseInsensitiveSearch] == NSOrderedSame) {
                                platform = LPKP_ANDROID;
                            }
                            break;
                        }
                        case 's':
                            staticKey = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'd':
                            dynamicKey = YES;
                            break;
                        default:
                            break;
                    }
                }
                
                // last argument should be lpk archive path
                optind++;
                if(argc > optind) {
                    archive = [NSString stringWithUTF8String:argv[optind]];
                    s_staticKey = staticKey;
                    s_dynamicKey = dynamicKey;
                    extract(archive, path, dst, lcid, platform);
                } else {
                    NSLog(@"you should specify lpk archive path");
                    ret = 1;
                    break;
                }
            } else if([@"patch" isEqualToString:cmd]) {
                NSString* to = nil;
                NSString* from = nil;
                BOOL noBackup = NO;
                int opt;
                const char* short_opts = "t:f:n";
                static struct option long_options[] = {
                    { "to", required_argument, NULL, 't' },
                    { "from", required_argument, NULL, 'f' },
                    { "nobak", no_argument, NULL, 'n' }
                };
                while((opt = getopt_long(argc, argv, short_opts, long_options, NULL)) != -1) {
                    switch (opt) {
                        case 't':
                            to = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'f':
                            from = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'n':
                            noBackup = YES;
                            break;
                        default:
                            break;
                    }
                }
                
                patch(to, from, noBackup);
            } else if([@"dump" isEqualToString:cmd]) {
                NSString* archive = nil;
                if(argc > 2) {
                    archive = [NSString stringWithUTF8String:argv[2]];
                    dump(archive);
                } else {
                    NSLog(@"you should specify lpk archive path");
                    ret = 1;
                    break;
                }
            } else {
                NSLog(@"unrecognized command %@", cmd);
                ret = 1;
                break;
            }
        } while(false);
    }
    
    return ret;
}
