//
//  LpkEntry.m
//  lpk
//
//  Created by maruojie on 15/2/16.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "LpkEntry.h"
#import "NSArray+Transform.h"
#import "NSString+Paths.h"

@implementation LpkEntry

@synthesize hash = _hash;

+ (LpkEntry*)decodeWithDictionary:(NSDictionary*)dict {
    LpkEntry* e = [[LpkEntry alloc] init];
    e.isDir = [[dict objectForKey:@"isDir"] boolValue];
    e.name = [dict objectForKey:@"name"];
    e.size = [[dict objectForKey:@"size"] unsignedIntValue];
    e.compressAlgorithm = (LPKCompressAlgorithm)[[dict objectForKey:@"compressAlgorithm"] intValue];
    e.encryptAlgorithm = (LPKEncryptAlgorithm)[[dict objectForKey:@"encryptAlgorithm"] intValue];
    e.realPath = [dict objectForKey:@"realPath"];
    {
        NSArray* children = [dict objectForKey:@"children"];
        for(NSDictionary* childDict in children) {
            LpkEntry* c = [LpkEntry decodeWithDictionary:childDict];
            [e.children addObject:c];
            c.parent = e;
        }
    }
    return e;
}

- (instancetype)init {
    if(self = [super init]) {
        self.children = [NSMutableArray array];
        self.filteredChildren = [NSMutableArray array];
        self.name = @"/";
        self.realPath = @"/";
        self.isDir = YES;
        return self;
    }
    return nil;
}

- (instancetype)initWithPath:(NSString*)path {
    if(self = [super init]) {
        // if it is not exist, ignore
        NSFileManager* fm = [NSFileManager defaultManager];
        if([fm fileExistsAtPath:path isDirectory:&_isDir]) {
            // if hidden, ignore
            self.name = [path lastPathComponent];
            if([self.name characterAtIndex:0] == '.')
                return nil;
            
            // if file, get size
            if(!self.isDir) {
                NSDictionary* attrs = [fm attributesOfItemAtPath:path error:nil];
                self.size = [[attrs objectForKey:NSFileSize] unsignedIntValue];
            }
            
            // save
            self.realPath = path;
            self.children = [NSMutableArray array];
            self.filteredChildren = [NSMutableArray array];
            return self;
        }
    }
    return nil;
}

- (instancetype)initWithFolderName:(NSString*)name {
    if(self = [super init]) {
        self.isDir = YES;
        self.name = name;
        self.realPath = @"";
        self.children = [NSMutableArray array];
        self.filteredChildren = [NSMutableArray array];
        return self;
    }
    return nil;
}

- (void)encodeWithDictionary:(NSMutableDictionary*)dict relativeTo:(NSString*)projectDir; {
    [dict setObject:[NSNumber numberWithBool:self.isDir] forKey:@"isDir"];
    [dict setObject:self.name forKey:@"name"];
    if([self.realPath isAbsolutePath]) {
        [dict setObject:[self.realPath stringWithPathRelativeTo:projectDir] forKey:@"realPath"];
    } else {
        [dict setObject:self.realPath forKey:@"realPath"];
    }
    [dict setObject:[NSNumber numberWithUnsignedInt:self.size] forKey:@"size"];
    [dict setObject:[NSNumber numberWithInt:self.compressAlgorithm] forKey:@"compressAlgorithm"];
    [dict setObject:[NSNumber numberWithInt:self.encryptAlgorithm] forKey:@"encryptAlgorithm"];
    {
        NSArray* encodedChildren = [self.children arrayByApplyingBlock:^id(id e) {
            NSMutableDictionary* childDict = [NSMutableDictionary dictionary];
            [e encodeWithDictionary:childDict relativeTo:projectDir];
            return childDict;
        }];
        [dict setObject:encodedChildren forKey:@"children"];
    }
}

- (BOOL)hasChild:(NSString*)name {
    for(LpkEntry* e in self.children) {
        if([e.name isEqualToString:name]) {
            return YES;
        }
    }
    return NO;
}

- (void)sortChildren {
    NSArray* sorted = [self.children sortedArrayUsingComparator:^NSComparisonResult(id obj1, id obj2) {
        LpkEntry* e1 = (LpkEntry*)obj1;
        LpkEntry* e2 = (LpkEntry*)obj2;
        if(e1.isDir == e2.isDir) {
            return [e1.name compare:e2.name];
        } else {
            return e1.isDir ? NSOrderedAscending : NSOrderedDescending;
        }
    }];
    self.children = [NSMutableArray arrayWithArray:sorted];
}

- (void)sortChildrenRecursively {
    [self sortChildren];
    for(LpkEntry* child in self.children) {
        [child sortChildrenRecursively];
    }
}

- (void)addChild:(LpkEntry*)e {
    [self.children addObject:e];
    e.parent = self;
}

- (void)removeChild:(LpkEntry*)e {
    [self.children removeObject:e];
    e.parent = nil;
}

- (void)removeFromParent {
    if(self.parent) {
        [self.parent removeChild:self];
    }
}

- (BOOL)isContainedByAnyDir:(NSArray*)dirs {
    LpkEntry* p = self.parent;
    while(p) {
        if([dirs containsObject:p]) {
            return YES;
        } else {
            p = p.parent;
        }
    }
    return NO;
}

- (LpkEntry*)childByName:(NSString*)name {
    for(LpkEntry* e in self.children) {
        if([e.name isEqualToString:name]) {
            return e;
        }
    }
    return nil;
}

- (NSString*)getKey {
    NSMutableArray* parts = [NSMutableArray array];
    LpkEntry* e = self;
    while(e) {
        if(e.parent) {
            [parts insertObject:e.name atIndex:0];
        } else {
            [parts insertObject:@"" atIndex:0];
        }
        e = e.parent;
    }
    return [parts componentsJoinedByString:@"/"];
}

- (void)rebuildFilterChildren:(NSString*)keyword {
    [self.filteredChildren removeAllObjects];
    for(LpkEntry* child in self.children) {
        if(child.isDir) {
            [child rebuildFilterChildren:keyword];
            if([child.filteredChildren count] > 0) {
                [self.filteredChildren addObject:child];
            }
        } else if([child.name rangeOfString:keyword options:NSCaseInsensitiveSearch].location != NSNotFound) {
            [self.filteredChildren addObject:child];
        }
    }
}

@end
