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
#import "lpk.h"
#import "LpkEntry.h"

@interface LpkBranchEntry : NSObject

@property (nonatomic, assign) BOOL markAsDeleted;
@property (nonatomic, strong) NSString* realPath;
@property (nonatomic, assign) LPKCompressAlgorithm compressAlgorithm;
@property (nonatomic, assign) LPKEncryptAlgorithm encryptAlgorithm;
@property (nonatomic, assign) uint16_t locale;
@property (nonatomic, assign) LPKPlatform platform;
@property (nonatomic, assign) uint32_t size;
@property (nonatomic, strong) LpkEntry* trunk;

+ (instancetype)decodeWithDictionary:(NSDictionary*)dict;

- (instancetype)initWithPath:(NSString*)path forTrunk:(LpkEntry*)trunk;
- (void)encodeWithDictionary:(NSMutableDictionary*)dict relativeTo:(NSString*)projectDir;

@end
