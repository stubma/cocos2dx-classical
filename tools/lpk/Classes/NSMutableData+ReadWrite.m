//
//  NSMutableData+ReadWrite.m
//  lpk
//
//  Created by maruojie on 15/2/23.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "NSMutableData+ReadWrite.h"

@implementation NSMutableData (ReadWrite)

- (void)writeUInt32:(uint32_t)v {
    [self writeUInt32:v littleEndian:YES];
}

- (void)writeUInt32:(uint32_t)v littleEndian:(BOOL)le {
    uint32_t _v = le ? CFSwapInt32HostToLittle(v) : CFSwapInt32HostToBig(v);
    [self appendBytes:&_v length:sizeof(uint32_t)];
}

- (void)writeUInt16:(uint16_t)v {
    [self writeUInt16:v littleEndian:YES];
}

- (void)writeUInt16:(uint16_t)v littleEndian:(BOOL)le {
    uint16_t _v = le ? CFSwapInt16HostToLittle(v) : CFSwapInt16HostToBig(v);
    [self appendBytes:&_v length:sizeof(uint16_t)];
}

@end
