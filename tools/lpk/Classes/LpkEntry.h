//
//  LpkEntry.h
//  lpk
//
//  Created by maruojie on 15/2/16.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>

static NSString* LPKC_NAMES[] = {
    @"N/A"
};

static NSString* LPKE_NAMES[] = {
    @"N/A"
};

@class LpkBranchEntry;

@interface LpkEntry : NSObject

@property (nonatomic, assign) BOOL isDir;
@property (nonatomic, assign) BOOL markAsDeleted;
@property (nonatomic, strong) NSString* name;
@property (nonatomic, strong) NSMutableArray* children;
@property (nonatomic, strong) NSMutableArray* filteredChildren;
@property (nonatomic, strong) NSMutableArray* branches;
@property (nonatomic, strong) LpkEntry* parent;
@property (nonatomic, readonly, getter=getKey) NSString* key;
@property (nonatomic, readonly, getter=getTotalSize) uint32_t totalSize;
@property (nonatomic, readonly, getter=getFirstBranch) LpkBranchEntry* firstBranch;

+ (LpkEntry*)decodeWithDictionary:(NSDictionary*)dict;

- (instancetype)initWithPath:(NSString*)path;
- (instancetype)initWithFolderName:(NSString*)name;
- (void)addChild:(LpkEntry*)e;
- (void)removeChild:(LpkEntry*)e;
- (void)removeFromParent;
- (void)sortChildren;
- (void)sortChildrenRecursively;
- (BOOL)isContainedByAnyDir:(NSArray*)dirs;
- (LpkEntry*)childByName:(NSString*)name;
- (BOOL)hasChild:(NSString*)name;
- (void)encodeWithDictionary:(NSMutableDictionary*)dict relativeTo:(NSString*)projectDir;
- (void)rebuildFilterChildren:(NSString*)keyword;
- (BOOL)hasLocale:(uint16_t)locale andPlatform:(uint16_t)platform;
- (int)getFileCountIncludeBranch;
- (void)collectFiles:(NSMutableArray*)ret;
- (void)markDeletedRecursively;
- (void)unmarkDeletedRecursively;

@end
