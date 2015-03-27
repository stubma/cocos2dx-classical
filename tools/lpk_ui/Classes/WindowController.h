//
//  WindowController.h
//  lpk
//
//  Created by maruojie on 15/2/15.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface WindowController : NSWindowController

@property (nonatomic, readonly, getter=getTree) TreeManager* tree;

@end
