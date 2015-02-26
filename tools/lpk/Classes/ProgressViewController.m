//
//  ProgressViewController.m
//  lpk
//
//  Created by maruojie on 15/2/23.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "ProgressViewController.h"

@interface ProgressViewController ()

- (IBAction)onAbort:(id)sender;

@end

@implementation ProgressViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

- (IBAction)onAbort:(id)sender {
    self.abort = YES;
}

@end
