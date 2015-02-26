//
//  ViewerViewController.h
//  lpk
//
//  Created by maruojie on 15/2/26.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewerViewController : NSViewController

@property (nonatomic, strong, setter=setBranch:) LpkBranchEntry* branch;

- (void)resetUI;

@end
