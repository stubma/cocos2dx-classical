//
//  NSArray+Transform.h
//  lpk
//
//  Created by maruojie on 15/2/16.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSArray (Transform)

- (NSArray*)arrayByApplyingBlock:(id(^)(id))block;

@end
