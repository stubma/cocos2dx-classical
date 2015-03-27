//
//  NSArray+Transform.m
//  lpk
//
//  Created by maruojie on 15/2/16.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "NSArray+Transform.h"

@implementation NSArray (Transform)

- (NSArray*)arrayByApplyingBlock:(id(^)(id))block{
    NSMutableArray* result = [NSMutableArray array];
    for(id x in self) {
        id obj = block(x);
        if(obj)
            [result addObject:obj];
    }
    return result;
}

@end
