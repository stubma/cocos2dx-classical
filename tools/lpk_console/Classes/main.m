//
//  main.m
//  lpk
//
//  Created by maruojie on 15/3/27.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <getopt.h>

static void usage() {
    NSLog(@"\nlpk command line tool usage:\n"
          "lpk [command] [options]\n\n"
          "command available:\n"
          "* help: show help of one command\n"
          "* make: create lpk archive from a root folder\n"
          "\t--root [path]: specify root folder of files to be packed\n"
          "\t--out [path]: the path of generated lpk archive, if not set, it will be generated at current\n"
          "\t\tdirectory with a default name\n"
          "\t--compress [none|zip]: set default compress algorithm for archive files, by default it is zip\n"
          "\t--encrypt [none|tea|xxtea|xor]: set default encrypt algorithm for files, by default it is none\n"
          "\t--static [key]: set static key for encryption\n"
          "\t--dynamic: set use dynamic key for encryption, currently the key is file name\n"
          "* extract: extract folder or file from lpk archive\n"
          "\t--path [path]: file path relative to archive root, such as /folder/a.txt\n"
          "\t--out [path]: path to save extracted file, if not set, will be saved at current directory\n"
          "\t[lpk]: lpk archive path\n"
          "* patch: patch a lpk archive with a patch lpk\n"
          "* dump: dump info of a lpk archive, such as file list, avaiable space\n");
}

static void make(NSString* root, NSString* dst, NSString* cmp, NSString* enc, NSString* staticKey, BOOL dynamicKey) {
    // validate arguments
    if(dst == nil) {
        dst = @"./out.lpk";
    }
    if(![@"none" isEqualToString:enc] && ![@"tea" isEqualToString:enc] && ![@"xxtea" isEqualToString:enc] && ![@"xor" isEqualToString:cmp]) {
        enc = @"none";
    }
    if(![enc isEqualToString:@"none"] && !dynamicKey && !staticKey) {
        enc = @"none";
    }
    if(![@"none" isEqualToString:cmp] && ![@"zip" isEqualToString:cmp]) {
        cmp = @"zip";
    }
    
    // normalize path
    root = [root stringByExpandingTildeInPath];
    dst = [dst stringByExpandingTildeInPath];
    
    
}

static void extract(NSString* archive, NSString* key, NSString* dst) {
    NSLog(@"extract, %@, %@, %@", archive, key, dst);
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
                BOOL dynamicKey = NO;
                int opt;
                const char* short_opts = "r:o:c:e:s:d";
                static struct option long_options[] = {
                    { "root", required_argument, NULL, 'r' },
                    { "out", required_argument, NULL, 'o' },
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
                make(root, dst, cmp, enc, staticKey, dynamicKey);
            } else if([@"extract" isEqualToString:cmd]) {
                NSString* archive = nil;
                NSString* dst = nil;
                NSString* path = nil;
                int opt;
                const char* short_opts = "p:o:";
                static struct option long_options[] = {
                    { "path", required_argument, NULL, 'p' },
                    { "out", required_argument, NULL, 'o' },
                };
                while((opt = getopt_long(argc, argv, short_opts, long_options, NULL)) != -1) {
                    switch (opt) {
                        case 'p':
                            path = [NSString stringWithUTF8String:optarg];
                            break;
                        case 'o':
                            dst = [NSString stringWithUTF8String:optarg];
                            break;
                        default:
                            break;
                    }
                }
                
                // last argument should be lpk archive path
                optind++;
                if(argc > optind) {
                    archive = [NSString stringWithUTF8String:argv[optind]];
                    extract(archive, path, dst);
                } else {
                    NSLog(@"you should specify lpk archive path");
                    ret = 1;
                    break;
                }
            } else if([@"patch" isEqualToString:cmd]) {
            } else if([@"dump" isEqualToString:cmd]) {
            } else {
                NSLog(@"unrecognized command %@", cmd);
                ret = 1;
                break;
            }
        } while(false);
    }
    
    return ret;
}
