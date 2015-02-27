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
    e.markAsDeleted = [[dict objectForKey:@"deleted"] boolValue];
    e.name = [dict objectForKey:@"name"];
    {
        NSArray* children = [dict objectForKey:@"children"];
        for(NSDictionary* childDict in children) {
            LpkEntry* c = [LpkEntry decodeWithDictionary:childDict];
            [e.children addObject:c];
            c.parent = e;
        }
    }
    if(!e.isDir) {
        e.branches = [NSMutableArray array];
        NSArray* branches = [dict objectForKey:@"branches"];
        for(NSDictionary* bDict in branches) {
            LpkBranchEntry* b = [LpkBranchEntry decodeWithDictionary:bDict];
            [e.branches addObject:b];
            b.trunk = e;
        }
    }
    return e;
}

- (instancetype)init {
    if(self = [super init]) {
        self.children = [NSMutableArray array];
        self.filteredChildren = [NSMutableArray array];
        self.name = @"/";
        self.isDir = YES;
        self.markAsDeleted = NO;
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
            
            // init members
            self.children = [NSMutableArray array];
            self.filteredChildren = [NSMutableArray array];
            
            // if file, add default branch
            if(!self.isDir) {
                LpkBranchEntry* b = [[LpkBranchEntry alloc] initWithPath:path forTrunk:self];
                self.branches = [NSMutableArray arrayWithObject:b];
            }
            
            return self;
        }
    }
    return nil;
}

- (instancetype)initWithFolderName:(NSString*)name {
    if(self = [super init]) {
        self.isDir = YES;
        self.name = name;
        self.children = [NSMutableArray array];
        self.filteredChildren = [NSMutableArray array];
        return self;
    }
    return nil;
}

- (void)encodeWithDictionary:(NSMutableDictionary*)dict relativeTo:(NSString*)projectDir; {
    [dict setObject:[NSNumber numberWithBool:self.isDir] forKey:@"isDir"];
    [dict setObject:[NSNumber numberWithBool:self.markAsDeleted] forKey:@"deleted"];
    [dict setObject:self.name forKey:@"name"];
    {
        NSArray* encodedChildren = [self.children arrayByApplyingBlock:^id(id e) {
            NSMutableDictionary* childDict = [NSMutableDictionary dictionary];
            [e encodeWithDictionary:childDict relativeTo:projectDir];
            return childDict;
        }];
        [dict setObject:encodedChildren forKey:@"children"];
    }
    if(!self.isDir) {
        NSArray* encodedBranches = [self.branches arrayByApplyingBlock:^id(id b) {
            NSMutableDictionary* bDict = [NSMutableDictionary dictionary];
            [b encodeWithDictionary:bDict relativeTo:projectDir];
            return bDict;
        }];
        [dict setObject:encodedBranches forKey:@"branches"];
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

- (void)markDeletedRecursively {
    self.markAsDeleted = YES;
    for(LpkEntry* child in self.children) {
        [child markDeletedRecursively];
    }
}

- (void)unmarkDeletedRecursively {
    self.markAsDeleted = NO;
    for(LpkEntry* child in self.children) {
        [child unmarkDeletedRecursively];
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

- (void)collectFiles:(NSMutableArray*)ret {
    for(LpkEntry* c in self.children) {
        if(!c.isDir) {
            [ret addObject:c];
        } else {
            [c collectFiles:ret];
        }
    }
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

- (uint32_t)getTotalSize {
    uint32_t size = 0;
    for(LpkBranchEntry* b in self.branches) {
        size += b.size;
    }
    return size;
}

- (LpkBranchEntry*)getFirstBranch {
    if([self.branches count] > 0) {
        return [self.branches objectAtIndex:0];
    } else {
        return nil;
    }
}

- (BOOL)hasLocale:(uint16_t)locale andPlatform:(uint16_t)platform {
    for(LpkBranchEntry* b in self.branches) {
        if(b.locale == locale && b.platform == platform) {
            return YES;
        }
    }
    return NO;
}

- (int)getFileCountIncludeBranch {
    // minus one because every entry has at least one branch
    int count = 0;
    if(!self.isDir)
        count += [self.branches count];
    for(LpkEntry* c in self.children) {
        if(c.isDir) {
            count += [c getFileCountIncludeBranch];
        } else {
            count += [c.branches count];
        }
    }
    return count;
}

@end
