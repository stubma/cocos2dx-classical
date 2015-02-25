//
//  CompressSettingViewController.m
//  lpk
//
//  Created by maruojie on 15/2/25.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "CompressSettingViewController.h"
#import "SettingsWindowController.h"

@interface CompressSettingViewController () <NSTableViewDataSource, NSTableViewDelegate>

@property (weak) IBOutlet NSTableView *tableView;

@end

@implementation CompressSettingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

#pragma mark -
#pragma mark tableview data source

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    // minus 1 to remove default
    return sizeof(COMPRESS_ALGORITHM_NAMES) / sizeof(NSString*) - 1;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    if([@"default_column" isEqualToString:tableColumn.identifier]) {
        return [NSNumber numberWithBool:tree.defaultCompressAlgorithm == row + 1];
    } else if([@"compress_algorithm_column" isEqualToString:tableColumn.identifier]) {
        return COMPRESS_ALGORITHM_NAMES[row + 1];
    } else {
        return nil;
    }
}

- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    if([@"default_column" isEqualToString:tableColumn.identifier]) {
        BOOL checked = [object boolValue];
        if(checked) {
            SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
            TreeManager* tree = w.tree;
            tree.defaultCompressAlgorithm = (LPKCompressAlgorithm)(row + 1);
            tree.dirty = YES;
            [tableView reloadData];
        }
    }
}

@end
