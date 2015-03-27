//
//  InputViewController.m
//  lpk
//
//  Created by maruojie on 15/2/16.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "InputViewController.h"

@interface InputViewController ()

- (IBAction)onOK:(id)sender;
- (IBAction)onCancel:(id)sender;

@end

@implementation InputViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

- (IBAction)onOK:(id)sender {
    [self.view.window.sheetParent endSheet:self.view.window returnCode:NSModalResponseOK];
}

- (IBAction)onCancel:(id)sender {
    [self.view.window.sheetParent endSheet:self.view.window returnCode:NSModalResponseCancel];
}

@end
