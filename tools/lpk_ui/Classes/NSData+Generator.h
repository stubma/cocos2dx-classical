//
//  NSData+Generator.h
//  lpk
//
//  Created by maruojie on 15/2/23.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (Generator)

+ (NSData*)dataWithByte:(uint8_t)b repeated:(size_t)len;

@end
