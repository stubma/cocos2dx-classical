//
//  TreeManager.h
//  lpk
//
//  Created by maruojie on 15/2/16.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ProgressViewController;

@interface TreeManager : NSObject

@property (nonatomic, strong) LpkEntry* root;
@property (nonatomic, strong) NSString* projectPath;
@property (nonatomic, strong) NSString* exportPath;
@property (nonatomic, assign) BOOL dirty;
@property (nonatomic, assign) LPKCompressAlgorithm defaultCompressAlgorithm;
@property (nonatomic, assign) LPKEncryptAlgorithm defaultEncryptAlgorithm;
@property (nonatomic, assign) BOOL autoSkipCompression;

- (NSArray*)stripContainedKeys:(NSArray*)keys;
- (NSArray*)stripContainedEntries:(NSArray*)entries;
- (void)addFiles:(NSArray*)paths toDir:(LpkEntry*)dir;
- (void)moveEntryByKeys:(NSArray*)keys toDir:(LpkEntry*)dir;
- (void)removeEntries:(NSArray*)entries;
- (void)removeEntry:(LpkEntry*)e;
- (void)removeBranch:(LpkBranchEntry*)b ofEntry:(LpkEntry*)e;
- (LpkEntry*)entryByKey:(NSString*)key;
- (void)newFolder:(NSString*)name toDir:(LpkEntry*)dir;
- (void)saveProject;
- (void)loadProject;
- (void)exportLPK:(ProgressViewController*)pvc;
- (void)rebuildFilterChildren:(NSString*)keyword;

@end
