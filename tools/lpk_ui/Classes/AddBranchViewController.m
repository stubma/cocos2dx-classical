//
//  AddBranchViewController.m
//  lpk
//
//  Created by maruojie on 15/2/19.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "AddBranchViewController.h"

@interface AddBranchViewController () <NSComboBoxDataSource>

@property (weak) IBOutlet NSTextField *pathLabel;

- (IBAction)onSelectFile:(id)sender;
- (IBAction)onCancel:(id)sender;
- (IBAction)onOK:(id)sender;

@end

@implementation AddBranchViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // init
    self.filePath = @"";
    [self.localeCombo setUsesDataSource:YES];
    [self.localeCombo setDataSource:self];
    [self.localeCombo selectItemAtIndex:0];
    [self.platformCombo setUsesDataSource:YES];
    [self.platformCombo setDataSource:self];
    [self.platformCombo selectItemAtIndex:0];
}

- (void)setFilePath:(NSString*)path {
    _filePath = path;
    self.pathLabel.stringValue = self.filePath;
}

- (IBAction)onSelectFile:(id)sender {
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg beginSheetModalForWindow:self.view.window completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            // Get an array containing the full filenames of all
            // files and directories selected.
            NSArray* urls = [openDlg URLs];
            NSString* filePath = [[urls objectAtIndex:0] path];
            self.filePath = filePath;
            self.pathLabel.stringValue = filePath;
        }
    }];
}

- (IBAction)onCancel:(id)sender {
    [self.view.window.sheetParent endSheet:self.view.window returnCode:NSModalResponseCancel];
}

- (IBAction)onOK:(id)sender {
    // check file is selected or not
    // check locale and platform is duplicated or not
    if([@"" isEqualToString:self.filePath]) {
        NSAlert* alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Please select file"];
        [alert beginSheetModalForWindow:self.view.window completionHandler:nil];
    } else {
        NSInteger index = [self.localeCombo indexOfSelectedItem];
        uint32_t lcid = 0;
        if(index > 0) {
            lcid = [NSLocale windowsLocaleCodeFromLocaleIdentifier:LOCALE_IDS[index]];
        }
        if([self.entry hasLocale:lcid andPlatform:[self.platformCombo indexOfSelectedItem]]) {
            NSAlert* alert = [[NSAlert alloc] init];
            [alert setMessageText:@"Combination of Locale and Platform already exists in current entry"];
            [alert beginSheetModalForWindow:self.view.window completionHandler:nil];
        } else {
            [self.view.window.sheetParent endSheet:self.view.window returnCode:NSModalResponseOK];
        }
    }
}

#pragma mark -
#pragma mark combo data source

- (NSInteger)numberOfItemsInComboBox:(NSComboBox *)aComboBox {
    if(aComboBox == self.localeCombo) {
        return [gLocaleDisplayNames count];
    } else {
        return sizeof(PLATFORM_NAMES) / sizeof(NSString*);
    }
}

- (id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index {
    if(aComboBox == self.localeCombo) {
        return [gLocaleDisplayNames objectAtIndex:index];
    } else {
        return PLATFORM_NAMES[index];
    }
}

@end
