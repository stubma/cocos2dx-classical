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

@interface LpkEntry : NSObject

@property (nonatomic, assign) BOOL isDir;
@property (nonatomic, strong) NSString* name;
@property (nonatomic, strong) NSString* realPath; // useless for dir
@property (nonatomic, assign) LPKCompressAlgorithm compressAlgorithm;
@property (nonatomic, assign) LPKEncryptAlgorithm encryptAlgorithm;
@property (nonatomic, assign) uint32_t size;
@property (nonatomic, strong) NSMutableArray* children;
@property (nonatomic, strong) NSMutableArray* filteredChildren;
@property (nonatomic, strong) NSMutableArray* group;
@property (nonatomic, strong) LpkEntry* parent;
@property (nonatomic, readonly, getter=getKey) NSString* key;

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

@end
