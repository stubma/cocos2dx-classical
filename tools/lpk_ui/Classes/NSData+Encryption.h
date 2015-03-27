//
//  NSData+Encryption.h
//  lpk
//
//  Created by maruojie on 15/2/26.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (Encryption)

- (NSData*)xorData:(NSString*)key;
- (NSData*)teaData:(NSString*)key;
- (NSData*)xxteaData:(NSString*)key;

@end
