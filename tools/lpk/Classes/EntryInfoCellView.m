//
//  EntryInfoCellView.m
//  lpk
//
//  Created by maruojie on 15/2/18.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "EntryInfoCellView.h"
#import "ViewController.h"
#import "AddBranchViewController.h"

@interface EntryInfoCellView () <NSComboBoxDataSource>

@property (weak) IBOutlet NSComboBox *localeCombo;
@property (weak) IBOutlet NSComboBox *platformCombo;
@property (weak) IBOutlet NSComboBox *compressCombo;
@property (weak) IBOutlet NSComboBox *encryptCombo;
@property (weak) IBOutlet NSTextField *pathLabel;

- (IBAction)onAddNewBranch:(id)sender;
- (IBAction)onShowInFinder:(id)sender;
- (IBAction)onDelete:(id)sender;
- (IBAction)onLocaleChanged:(id)sender;
- (IBAction)onPlatformChanged:(id)sender;

@end

@implementation EntryInfoCellView

- (void)drawRect:(NSRect)dirtyRect {
    NSRect selectionRect = NSInsetRect(self.bounds, 2.5, 2.5);
    [[NSColor colorWithCalibratedWhite:.65 alpha:1.0] setStroke];
    [[NSColor colorWithCalibratedWhite:.82 alpha:1.0] setFill];
    NSBezierPath *selectionPath = [NSBezierPath bezierPathWithRoundedRect:selectionRect xRadius:10 yRadius:10];
    [selectionPath fill];
    [selectionPath stroke];
}

- (void)setObjectValue:(id)objectValue {
    [super setObjectValue:objectValue];
    
    // set data source for combo
    [self.localeCombo setDataSource:self];
    [self.platformCombo setDataSource:self];
    [self.compressCombo setDataSource:self];
    [self.encryptCombo setDataSource:self];
    
    // init UI
    LpkBranchEntry* b = (LpkBranchEntry*)objectValue;
    self.pathLabel.stringValue = b.realPath;
    [self.platformCombo selectItemAtIndex:b.platform];
    NSString* localeId = [NSLocale localeIdentifierFromWindowsLocaleCode:b.locale];
    NSLocale* locale = [NSLocale localeWithLocaleIdentifier:@"en_US"];
    NSString* displayName = [locale displayNameForKey:NSLocaleIdentifier value:localeId];
    if([@"Root" isEqualToString:displayName])
        displayName = @"Default";
    [self.localeCombo selectItemAtIndex:[gLocaleDisplayNames indexOfObject:displayName]];
    [self.compressCombo selectItemAtIndex:b.compressAlgorithm];
    [self.encryptCombo selectItemAtIndex:b.encryptAlgorithm];
}

- (IBAction)onAddNewBranch:(id)sender {
    LpkBranchEntry* b = (LpkBranchEntry*)self.objectValue;
    NSStoryboard* sb = [NSStoryboard storyboardWithName:@"Main" bundle:nil];
    NSWindowController* add = [sb instantiateControllerWithIdentifier:@"add_branch"];
    AddBranchViewController* vc = (AddBranchViewController*)add.contentViewController;
    vc.entry = b.trunk;
    [self.window beginSheet:add.window completionHandler:^(NSModalResponse returnCode) {
        if(returnCode == NSModalResponseOK) {
            // create branch
            LpkBranchEntry* newb = [[LpkBranchEntry alloc] initWithPath:vc.filePath forTrunk:b.trunk];
            
            // set locale
            NSInteger index = [vc.localeCombo indexOfSelectedItem];
            uint32_t lcid = 0;
            if(index > 0) {
                lcid = [NSLocale windowsLocaleCodeFromLocaleIdentifier:LOCALE_IDS[index]];
            }
            newb.locale = lcid;
            
            // set platform
            newb.platform = (LPKPlatform)[vc.platformCombo indexOfSelectedItem];
            
            // add branch
            [b.trunk.branches addObject:newb];
            
            // flag dirty and reload info table
            ViewController* vc = (ViewController*)self.window.contentViewController;
            vc.tree.dirty = YES;
            [vc reloadInfoTable];
        }
    }];
}

- (IBAction)onShowInFinder:(id)sender {
    LpkBranchEntry* b = (LpkBranchEntry*)self.objectValue;
    ViewController* vc = (ViewController*)self.window.contentViewController;
    NSString* path = b.realPath;
    if(![path isAbsolutePath]) {
        path = [[vc.tree.projectPath stringByDeletingLastPathComponent] stringByAppendingPathComponent:b.realPath];
        path = [path stringByStandardizingPath];
    }
    NSArray* fileUrls = [NSArray arrayWithObject:[NSURL fileURLWithPath:path isDirectory:NO]];
    [[NSWorkspace sharedWorkspace] activateFileViewerSelectingURLs:fileUrls];
}

- (IBAction)onDelete:(id)sender {
    LpkBranchEntry* b = (LpkBranchEntry*)self.objectValue;
    LpkEntry* trunk = b.trunk;
    ViewController* vc = (ViewController*)self.window.contentViewController;
    if([trunk.branches count] == 1) {
        [vc.tree removeEntry:trunk];
        [vc reloadFileOutline];
        [vc reloadInfoTable];
    } else {
        [vc.tree removeBranch:b ofEntry:trunk];
        [vc reloadInfoTable];
    }
}

- (IBAction)onLocaleChanged:(id)sender {
    // get lcid from index
    NSInteger index = [self.localeCombo indexOfSelectedItem];
    uint32_t lcid = 0;
    if(index > 0) {
        lcid = [NSLocale windowsLocaleCodeFromLocaleIdentifier:LOCALE_IDS[index]];
    }
    
    // save back to branch
    LpkBranchEntry* b = (LpkBranchEntry*)self.objectValue;
    b.locale = lcid;
    
    // flag
    ViewController* vc = (ViewController*)self.window.contentViewController;
    vc.tree.dirty = YES;
}

- (IBAction)onPlatformChanged:(id)sender {
    // save in branch
    LpkBranchEntry* b = (LpkBranchEntry*)self.objectValue;
    b.platform = (LPKPlatform)[self.platformCombo indexOfSelectedItem];
    
    // flag
    ViewController* vc = (ViewController*)self.window.contentViewController;
    vc.tree.dirty = YES;
}

#pragma mark -
#pragma mark combo data source

- (NSInteger)numberOfItemsInComboBox:(NSComboBox *)aComboBox {
    if(aComboBox == self.localeCombo) {
        return [gLocaleDisplayNames count];
    } else if(aComboBox == self.platformCombo) {
        return sizeof(PLATFORM_NAMES) / sizeof(NSString*);
    } else if(aComboBox == self.compressCombo) {
        return sizeof(COMPRESS_ALGORITHM_NAMES) / sizeof(NSString*);
    } else if(aComboBox == self.encryptCombo) {
        return sizeof(ENCRYPT_ALGORITHM_NAMES) / sizeof(NSString*);
    } else {
        return 0;
    }
}

- (id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index {
    if(aComboBox == self.localeCombo) {
        return [gLocaleDisplayNames objectAtIndex:index];
    } else if(aComboBox == self.platformCombo) {
        return PLATFORM_NAMES[index];
    } else if(aComboBox == self.compressCombo) {
        return COMPRESS_ALGORITHM_NAMES[index];
    } else if(aComboBox == self.encryptCombo) {
        return ENCRYPT_ALGORITHM_NAMES[index];
    } else {
        return nil;
    }
}

@end
