//
//  LpkBranchEntry.h
//  lpk
//
//  Created by maruojie on 15/2/18.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LpkBranchEntry : NSObject

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
