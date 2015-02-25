//
//  Consts.m
//  lpk
//
//  Created by maruojie on 15/2/19.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "Consts.h"

NSString* LOCALE_IDS[] = {
    @"Default",
    @"en",
    @"en_US",
    @"en_UK",
    @"zh",
    @"zh_CN",
    @"zh_TW",
    @"zh_HK"
};
NSMutableArray* gLocaleDisplayNames = nil;

NSString* PLATFORM_NAMES[] = {
    @"Default",
    @"iOS",
    @"Android"
};

NSString* COMPRESS_ALGORITHM_NAMES[] = {
    @"Not Compressed",
    @"Zlib"
};

NSString* ENCRYPT_ALGORITHM_NAMES[] = {
    @"Not Encrypted",
    @"XOR",
    @"TEA",
    @"XXTEA"
};

void initConsts() {
    if(!gLocaleDisplayNames) {
        NSLocale* locale = [NSLocale localeWithLocaleIdentifier:@"en_US"];
        gLocaleDisplayNames = [NSMutableArray array];
        [gLocaleDisplayNames addObject:LOCALE_IDS[0]];
        int c = sizeof(LOCALE_IDS) / sizeof(NSString*);
        for(int i = 1; i < c; i++) {
            [gLocaleDisplayNames addObject:[locale displayNameForKey:NSLocaleIdentifier value:LOCALE_IDS[i]]];
        }
    }
}