//
//  ProgressViewController.h
//  lpk
//
//  Created by maruojie on 15/2/23.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ProgressViewController : NSViewController

@property (weak) IBOutlet NSProgressIndicator *progressIndicator;
@property (weak) IBOutlet NSTextField *hintLabel;
@property (nonatomic, assign) BOOL abort;

@end
