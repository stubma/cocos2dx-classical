//
//  LpkBranchEntry.m
//  lpk
//
//  Created by maruojie on 15/2/18.
//  Copyright (c) 2015年 luma. All rights reserved.
//

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
