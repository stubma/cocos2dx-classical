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
#import "LpkBranchEntry.h"
#import "NSString+Paths.h"

@implementation LpkBranchEntry

+ (instancetype)decodeWithDictionary:(NSDictionary*)dict {
    LpkBranchEntry* b = [[LpkBranchEntry alloc] init];
    b.realPath = [dict objectForKey:@"realPath"];
    b.markAsDeleted = [[dict objectForKey:@"deleted"] boolValue];
    b.size = [[dict objectForKey:@"size"] intValue];
    b.compressAlgorithm = (LPKCompressAlgorithm)[[dict objectForKey:@"compressAlgorithm"] intValue];
    b.encryptAlgorithm = (LPKEncryptAlgorithm)[[dict objectForKey:@"encryptAlgorithm"] intValue];
    b.locale = [[dict objectForKey:@"locale"] intValue];
    b.platform = (LPKPlatform)[[dict objectForKey:@"platform"] intValue];
    return b;
}

- (instancetype)init {
    if(self = [super init]) {
        self.realPath = @"";
        self.markAsDeleted = NO;
        return self;
    }
    return nil;
}

- (instancetype)initWithPath:(NSString*)path forTrunk:(LpkEntry*)trunk; {
    if(self = [super init]) {
        // if it is not exist, ignore
        NSFileManager* fm = [NSFileManager defaultManager];
        BOOL isDir;
        if([fm fileExistsAtPath:path isDirectory:&isDir]) {
            if(!isDir) {
                self.trunk = trunk;
                self.realPath = path;
                NSDictionary* attrs = [fm attributesOfItemAtPath:path error:nil];
                self.size = [[attrs objectForKey:NSFileSize] unsignedIntValue];
                return self;
            }
        }
    }
    return nil;
}

- (void)encodeWithDictionary:(NSMutableDictionary*)dict relativeTo:(NSString*)projectDir {
    if([self.realPath isAbsolutePath]) {
        [dict setObject:[self.realPath stringWithPathRelativeTo:projectDir] forKey:@"realPath"];
    } else {
        [dict setObject:self.realPath forKey:@"realPath"];
    }
    [dict setObject:[NSNumber numberWithUnsignedInt:self.size] forKey:@"size"];
    [dict setObject:[NSNumber numberWithInt:self.compressAlgorithm] forKey:@"compressAlgorithm"];
    [dict setObject:[NSNumber numberWithInt:self.encryptAlgorithm] forKey:@"encryptAlgorithm"];
    [dict setObject:[NSNumber numberWithInt:self.locale] forKey:@"locale"];
    [dict setObject:[NSNumber numberWithInt:self.platform] forKey:@"platform"];
    [dict setObject:[NSNumber numberWithBool:self.markAsDeleted] forKey:@"deleted"];
}

@end
