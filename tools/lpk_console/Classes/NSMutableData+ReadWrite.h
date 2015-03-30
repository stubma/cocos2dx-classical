//
//  NSMutableData+ReadWrite.h
//  lpk
//
//  Created by maruojie on 15/2/23.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableData (ReadWrite)

- (void)writeUInt32:(uint32_t)v;
- (void)writeUInt32:(uint32_t)v littleEndian:(BOOL)le;
- (void)writeUInt16:(uint16_t)v;
- (void)writeUInt16:(uint16_t)v littleEndian:(BOOL)le;

@end
