//
//  NSString+Paths.h
//  lpk
//
//  Created by maruojie on 15/2/17.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (Paths)

- (NSString*)stringWithPathRelativeTo:(NSString*)anchorPath;

@end
