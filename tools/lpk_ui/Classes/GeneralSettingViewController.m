//
//  GeneralSettingViewController.m
//  lpk
//
//  Created by maruojie on 15/2/26.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "GeneralSettingViewController.h"
#import "SettingsWindowController.h"

@interface GeneralSettingViewController ()

@property (weak) IBOutlet NSTextField *blockSizeText;
@property (weak) IBOutlet NSStepper *stepper;

- (IBAction)onBlockSizeChanged:(id)sender;

@end

@implementation GeneralSettingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

- (void)viewDidAppear {
    [super viewDidAppear];
    
    // init control
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    self.blockSizeText.stringValue = [NSString stringWithFormat:@"%d", 512 << tree.blockSize];
    self.stepper.integerValue = tree.blockSize;
}

- (IBAction)onBlockSizeChanged:(id)sender {
    NSStepper* s = (NSStepper*)sender;
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    tree.blockSize = (int)s.integerValue;
    tree.dirty = YES;
    self.blockSizeText.stringValue = [NSString stringWithFormat:@"%d", 512 << tree.blockSize];
}

@end
