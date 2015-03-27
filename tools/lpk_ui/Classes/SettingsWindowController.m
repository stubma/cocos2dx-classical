//
//  SettingsWindowController.m
//  lpk
//
//  Created by maruojie on 15/2/25.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "SettingsWindowController.h"
#import "SettingsViewController.h"

@interface SettingsWindowController ()

@property (weak) IBOutlet NSToolbar *toolbar;
- (IBAction)onGeneral:(id)sender;
- (IBAction)onCompress:(id)sender;
- (IBAction)onEncryption:(id)sender;

@end

@implementation SettingsWindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // select first
    [self.toolbar setSelectedItemIdentifier:@"general"];
}

- (IBAction)onGeneral:(id)sender {
    SettingsViewController* vc = (SettingsViewController*)self.contentViewController;
    [vc.tabView selectTabViewItemWithIdentifier:@"general"];
}

- (IBAction)onCompress:(id)sender {
    SettingsViewController* vc = (SettingsViewController*)self.contentViewController;
    [vc.tabView selectTabViewItemWithIdentifier:@"compress"];
}

- (IBAction)onEncryption:(id)sender {
    SettingsViewController* vc = (SettingsViewController*)self.contentViewController;
    [vc.tabView selectTabViewItemWithIdentifier:@"encryption"];
}

@end
