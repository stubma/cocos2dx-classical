//
//  NSData+Generator.m
//  lpk
//
//  Created by maruojie on 15/2/23.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "NSData+Generator.h"

@implementation NSData (Generator)

+ (NSData*)dataWithByte:(uint8_t)b repeated:(size_t)len {
    uint8_t* tmp = (uint8_t*)malloc(sizeof(uint8_t) * len);
    memset(tmp, b, len);
    NSData* d = [NSData dataWithBytes:tmp length:len];
    free(tmp);
    return d;
}

@end
