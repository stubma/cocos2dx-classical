//
//  EncryptionSettingViewController.m
//  lpk
//
//  Created by maruojie on 15/2/26.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "EncryptionSettingViewController.h"
#import "SettingsWindowController.h"

@interface EncryptionSettingViewController () <NSComboBoxDataSource, NSTextFieldDelegate>

@property (weak) IBOutlet NSComboBox *defaultCombo;
@property (weak) IBOutlet NSTextField *xorStaticKeyText;
@property (weak) IBOutlet NSButton *xorStaticKeyCheckbox;
@property (weak) IBOutlet NSButton *xorDynamicKeyCheckbox;
@property (weak) IBOutlet NSTextField *teaStaticKeyText;
@property (weak) IBOutlet NSButton *teaStaticKeyCheckbox;
@property (weak) IBOutlet NSButton *teaDynamicKeyCheckbox;
@property (weak) IBOutlet NSTextField *xxteaStaticKeyText;
@property (weak) IBOutlet NSButton *xxteaStaticKeyCheckbox;
@property (weak) IBOutlet NSButton *xxteaDynamicKeyCheckbox;

- (IBAction)onDefaultAlgorithmChanged:(id)sender;
- (IBAction)onXorStaticKeyChecked:(id)sender;
- (IBAction)onXorDynamicKeyChecked:(id)sender;
- (IBAction)onTeaStaticKeyChecked:(id)sender;
- (IBAction)onTeaDynamicKeyChecked:(id)sender;
- (IBAction)onXxteaStaticKeyChecked:(id)sender;
- (IBAction)onXxteaDynamicKeyChecked:(id)sender;

@end

@implementation EncryptionSettingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Do view setup here.
    [self.defaultCombo setDataSource:self];
}

- (void)viewDidAppear {
    [super viewDidAppear];
    
    // init combo
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    [self.defaultCombo selectItemAtIndex:tree.defaultEncryptAlgorithm - 1];
    
    // init xor
    self.xorStaticKeyCheckbox.state = tree.xorDynamicKey ? NSOffState : NSOnState;
    self.xorDynamicKeyCheckbox.state = tree.xorDynamicKey ? NSOnState : NSOffState;
    self.xorStaticKeyText.stringValue = tree.xorStaticKey;
    
    // init tea
    self.teaStaticKeyCheckbox.state = tree.teaDynamicKey ? NSOffState : NSOnState;
    self.teaDynamicKeyCheckbox.state = tree.teaDynamicKey ? NSOnState : NSOffState;
    self.teaStaticKeyText.stringValue = tree.teaStaticKey;
    
    // init xxtea
    self.xxteaStaticKeyCheckbox.state = tree.xxteaDynamicKey ? NSOffState : NSOnState;
    self.xxteaDynamicKeyCheckbox.state = tree.xxteaDynamicKey ? NSOnState : NSOffState;
    self.xxteaStaticKeyText.stringValue = tree.xxteaStaticKey;
}

#pragma mark -
#pragma mark combo data source

- (NSInteger)numberOfItemsInComboBox:(NSComboBox *)aComboBox {
    return sizeof(ENCRYPT_ALGORITHM_NAMES) / sizeof(NSString*) - 1;
}

- (id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index {
    return ENCRYPT_ALGORITHM_NAMES[index + 1];
}

#pragma mark -
#pragma mark text delegate

- (void)controlTextDidChange:(NSNotification *)obj {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    if(obj.object == self.xorStaticKeyText) {
        tree.xorStaticKey = self.xorStaticKeyText.stringValue;
        tree.dirty = YES;
    } else if(obj.object == self.teaStaticKeyText) {
        tree.teaStaticKey = self.teaStaticKeyText.stringValue;
        tree.dirty = YES;
    } else if(obj.object == self.xxteaStaticKeyText) {
        tree.xxteaStaticKey = self.xxteaStaticKeyText.stringValue;
        tree.dirty = YES;
    }
}

#pragma mark -
#pragma mark IBAction

- (IBAction)onDefaultAlgorithmChanged:(id)sender {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    tree.defaultEncryptAlgorithm = (LPKEncryptAlgorithm)([self.defaultCombo indexOfSelectedItem] + 1);
    tree.dirty = YES;
}

- (IBAction)onXorStaticKeyChecked:(id)sender {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    self.xorDynamicKeyCheckbox.state = NSOffState;
    tree.xorDynamicKey = NO;
    tree.dirty = YES;
}

- (IBAction)onXorDynamicKeyChecked:(id)sender {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    self.xorStaticKeyCheckbox.state = NSOffState;
    tree.xorDynamicKey = YES;
    tree.dirty = YES;
}

- (IBAction)onTeaStaticKeyChecked:(id)sender {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    self.teaDynamicKeyCheckbox.state = NSOffState;
    tree.teaDynamicKey = NO;
    tree.dirty = YES;
}

- (IBAction)onTeaDynamicKeyChecked:(id)sender {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    self.teaStaticKeyCheckbox.state = NSOffState;
    tree.teaDynamicKey = YES;
    tree.dirty = YES;
}

- (IBAction)onXxteaStaticKeyChecked:(id)sender {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    self.xxteaDynamicKeyCheckbox.state = NSOffState;
    tree.xxteaDynamicKey = NO;
    tree.dirty = YES;
}

- (IBAction)onXxteaDynamicKeyChecked:(id)sender {
    SettingsWindowController* w = (SettingsWindowController*)self.view.window.windowController;
    TreeManager* tree = w.tree;
    self.xxteaStaticKeyCheckbox.state = NSOffState;
    tree.xxteaDynamicKey = YES;
    tree.dirty = YES;
}

@end
