//
//  NSOutlineView+State.h
//  lpk
//
//  Created by maruojie on 15/2/17.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSOutlineView (State)

- (NSArray *)expandedItems;
- (void)expandItems:(NSArray*)array;

@end
