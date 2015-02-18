//
//  NSOutlineView+State.m
//  lpk
//
//  Created by maruojie on 15/2/17.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "NSOutlineView+State.h"

@implementation NSOutlineView (State)

- (NSArray *)expandedItems {
    NSMutableArray *expandedItemsArray = [NSMutableArray array];
    NSUInteger row, numberOfRows = [self numberOfRows];
    
    for (row = 0 ; row < numberOfRows ; row++) {
        id item = [self itemAtRow:row];
        if ([self isItemExpanded:item])
            [expandedItemsArray addObject:item];
    }
    
    return expandedItemsArray;
}

- (void)expandItems:(NSArray *)array {
    for (id savedItem in array) {
        [self expandItem:savedItem];
    }
}

@end
