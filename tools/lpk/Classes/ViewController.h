//
//  ViewController.h
//  lpk
//
//  Created by maruojie on 15/2/15.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewController : NSViewController

@property (strong) TreeManager* tree;
@property (nonatomic, strong, setter=setFilterKeyword:) NSString* filterKeyword;

- (LpkEntry*)getFirstSelectedItem;
- (void)reloadFileOutline;
- (IBAction)onDelete:(id)sender;

@end

