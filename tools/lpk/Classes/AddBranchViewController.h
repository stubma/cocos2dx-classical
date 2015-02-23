//
//  AddBranchViewController.h
//  lpk
//
//  Created by maruojie on 15/2/19.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AddBranchViewController : NSViewController

@property (weak) IBOutlet NSComboBox *localeCombo;
@property (weak) IBOutlet NSComboBox *platformCombo;
@property (nonatomic, strong) LpkEntry* entry;
@property (nonatomic, strong, setter=setFilePath:) NSString* filePath;

@end
