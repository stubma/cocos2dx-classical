//
//  ExtractViewController.m
//  lpk
//
//  Created by maruojie on 15/3/8.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "ExtractViewController.h"

@interface ExtractViewController () <NSComboBoxDataSource>

@property (weak) IBOutlet NSTextField *lpkFileText;
@property (weak) IBOutlet NSTextField *filePathText;
@property (weak) IBOutlet NSComboBox *localeCombo;
@property (weak) IBOutlet NSComboBox *platformCombo;
@property (weak) IBOutlet NSTextField *dstDirText;
@property (weak) IBOutlet NSTextField *staticKeyText;
@property (nonatomic, strong) NSString* dstDir;
@property (nonatomic, strong) NSString* lpkFilePath;

- (IBAction)onSelectLPKFile:(id)sender;
- (IBAction)onSelectDstDir:(id)sender;
- (IBAction)onExtract:(id)sender;
- (IBAction)onCancel:(id)sender;

@end

@implementation ExtractViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // init combo
    [self.localeCombo setDataSource:self];
    [self.platformCombo setDataSource:self];
    [self.localeCombo selectItemAtIndex:0];
    [self.platformCombo selectItemAtIndex:0];
    
    // init dst dir
    self.dstDir = [@"~/Desktop" stringByExpandingTildeInPath];
    self.dstDirText.stringValue = self.dstDir;
}

- (IBAction)onSelectLPKFile:(id)sender {
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg setAllowedFileTypes:@[@"lpk"]];
    [openDlg beginSheetModalForWindow:self.view.window completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            NSArray* urls = [openDlg URLs];
            NSString* filePath = [[urls objectAtIndex:0] path];
            self.lpkFilePath = filePath;
            self.lpkFileText.stringValue = filePath;
        }
    }];
}

- (IBAction)onSelectDstDir:(id)sender {
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setCanChooseFiles:NO];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg beginSheetModalForWindow:self.view.window completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            NSArray* urls = [openDlg URLs];
            NSString* filePath = [[urls objectAtIndex:0] path];
            self.dstDir = filePath;
            self.dstDirText.stringValue = filePath;
        }
    }];
}

- (IBAction)onExtract:(id)sender {
    lpk_file lpk;
    int result = lpk_open_file(&lpk, [self.lpkFilePath cStringUsingEncoding:NSUTF8StringEncoding]);
    if(result != 0) {
        NSLog(@"lpk_open_file, open source error: %d", result);
        return;
    }
    
    // extract
    uint32_t lcid = 0;
    if([self.localeCombo indexOfSelectedItem] > 0) {
        lcid = [NSLocale windowsLocaleCodeFromLocaleIdentifier:self.localeCombo.stringValue];
    }
    uint32_t size;
    uint8_t* buf = lpk_extract_file(&lpk,
                                    [self.filePathText.stringValue cStringUsingEncoding:NSUTF8StringEncoding],
                                    &size,
                                    [self.staticKeyText.stringValue cStringUsingEncoding:NSUTF8StringEncoding],
                                    (uint32_t)[self.staticKeyText.stringValue lengthOfBytesUsingEncoding:NSUTF8StringEncoding],
                                    lcid,
                                    (LPKPlatform)[self.platformCombo indexOfSelectedItem]);
    if(buf) {
        NSData* data = [NSData dataWithBytes:buf length:size];
        [data writeToFile:[self.dstDir stringByAppendingPathComponent:[self.filePathText.stringValue lastPathComponent]] atomically:YES];
        free(buf);
    } else {
        NSLog(@"extract failed");
    }
    
    // close lpk
    lpk_close_file(&lpk);
    
    // end sheet
    [self.view.window.sheetParent endSheet:self.view.window returnCode:NSModalResponseOK];
}

- (IBAction)onCancel:(id)sender {
    [self.view.window.sheetParent endSheet:self.view.window returnCode:NSModalResponseCancel];
}

#pragma mark -
#pragma mark combo data source

- (NSInteger)numberOfItemsInComboBox:(NSComboBox *)aComboBox {
    if(aComboBox == self.localeCombo) {
        return [gLocaleDisplayNames count];
    } else if(aComboBox == self.platformCombo) {
        return sizeof(PLATFORM_NAMES) / sizeof(NSString*);
    } else {
        return 0;
    }
}

- (id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index {
    if(aComboBox == self.localeCombo) {
        return [gLocaleDisplayNames objectAtIndex:index];
    } else if(aComboBox == self.platformCombo) {
        return PLATFORM_NAMES[index];
    } else {
        return nil;
    }
}

@end