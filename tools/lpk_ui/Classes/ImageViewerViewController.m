//
//  ImageViewerViewController.m
//  lpk
//
//  Created by maruojie on 15/2/26.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "ImageViewerViewController.h"

@interface ImageViewerViewController ()

@property (weak) IBOutlet NSImageView *imageView;
@property (weak) IBOutlet NSTextField *infoLabel;

@end

@implementation ImageViewerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do view setup here.
}

- (void)resetUI {
    [super resetUI];
    
    self.imageView.image = [[NSImage alloc] initWithContentsOfFile:self.branch.realPath];
    self.infoLabel.stringValue = [NSString stringWithFormat:@"%dx%d", (int)self.imageView.image.size.width, (int)self.imageView.image.size.height];
}

@end
