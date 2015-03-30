//
//  NSData+Encryption.m
//  lpk
//
//  Created by maruojie on 15/2/26.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "NSData+Encryption.h"
#import "support/codec/xxtea.h"

@implementation NSData (Encryption)

- (NSData*)xorData:(NSString*)key {
    NSMutableData* enc = [NSMutableData dataWithData:self];
    const uint8_t* keyBytes = (const uint8_t*)[key cStringUsingEncoding:NSUTF8StringEncoding];
    uint32_t keyLen = (uint32_t)[key lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    uint8_t* plain = (uint8_t*)[enc mutableBytes];
    uint32_t plainLen = (uint32_t)[self length];
    for(uint32_t i = 0; i < plainLen; i += keyLen) {
        uint32_t remain = MIN(keyLen, plainLen - i);
        for(uint32_t j = 0; j < remain; j++) {
            plain[i + j] ^= keyBytes[j];
        }
    }
    return [NSData dataWithData:enc];
}

- (NSData*)teaData:(NSString*)key {
    // encrypt
    int outLen;
    const char* enc = teaenc([key cStringUsingEncoding:NSUTF8StringEncoding],
                             (int)[key lengthOfBytesUsingEncoding:NSUTF8StringEncoding],
                             [self bytes],
                             (int)[self length],
                             0,
                             (int)[self length], &outLen);
    NSData* ret = [NSData dataWithBytes:enc length:outLen];
    free((void*)enc);
    return ret;
}

- (NSData*)xxteaData:(NSString*)key {
    xxtea_long outLen;
    unsigned char* enc = xxtea_encrypt((unsigned char*)[self bytes],
                                       (xxtea_long)[self length],
                                       (unsigned char*)[key cStringUsingEncoding:NSUTF8StringEncoding],
                                       (xxtea_long)[key lengthOfBytesUsingEncoding:NSUTF8StringEncoding],
                                       &outLen);
    NSData* ret = [NSData dataWithBytes:enc length:outLen];
    free((void*)enc);
    return ret;
}

@end
