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
          "\t--to [path]: destination lpk archive to be patched\n"
          "\t--from [path]: patch lpk file\n"
          "\t--nobak: if set, destination lpk archive will not be backuped\n"
          "* dump: dump info of a lpk archive, such as file list, avaiable space\n"
          "\t[lpk]: specify lpk archive you want to dump\n");
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
    root = [[root stringByExpandingTildeInPath] stringByStandardizingPath];
    dst = [[dst stringByExpandingTildeInPath] stringByStandardizingPath];
    
    
}

static void extract(NSString* archive, NSString* key, NSString* dst) {
    // validate
    if(!key) {
        NSLog(@"please specify file path you want to extract");
        return;
    }
    if(!dst) {
        dst = [NSString stringWithFormat:@"./%@", [key lastPathComponent]];
    }
    
    // normalize path
    dst = [[dst stringByExpandingTildeInPath] stringByStandardizingPath];
    archive = [[archive stringByExpandingTildeInPath] stringByStandardizingPath];
    
    // validate archive existence
    NSFileManager* fm = [NSFileManager defaultManager];
    if(![fm fileExistsAtPath:archive]) {
        NSLog(@"lpk archive doesn't not exist");
        return;
    }
    
    
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
                    { "out", required_argument, NULL, 'o' }
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
