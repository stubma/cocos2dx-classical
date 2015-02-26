//
//  ViewerViewController.m
//  lpk
//
//  Created by maruojie on 15/2/26.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "ViewerViewController.h"

@interface ViewerViewController ()

@end

@implementation ViewerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

- (void)setBranch:(LpkBranchEntry*)b {
    _branch = b;
    [self resetUI];
}

- (void)resetUI {
    // subclass need implement it
}

@end
