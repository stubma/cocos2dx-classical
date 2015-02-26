//
//  DefaultViewerViewController.m
//  lpk
//
//  Created by maruojie on 15/2/26.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "DefaultViewerViewController.h"

@interface DefaultViewerViewController ()

@property (weak) IBOutlet NSImageView *iconView;
@property (weak) IBOutlet NSTextField *nameLabel;

@end

@implementation DefaultViewerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

- (void)resetUI {
    [super resetUI];
    
    // set icon
    NSImage* icon = [[NSWorkspace sharedWorkspace] iconForFile:self.branch.realPath];
    [icon setSize:NSMakeSize(200, 200)];
    self.iconView.image = icon;
    self.nameLabel.stringValue = [self.branch.realPath lastPathComponent];
}

@end
