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

static NSString* LPKC_NAMES[] = {
    @"N/A"
};

static NSString* LPKE_NAMES[] = {
    @"N/A"
};

@class LpkBranchEntry;

@interface LpkEntry : NSObject

@property (nonatomic, assign) BOOL isDir;
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
- (int)deletedBranchCount;

@end
