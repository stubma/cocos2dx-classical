//
//  WindowController.m
//  lpk
//
//  Created by maruojie on 15/2/15.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "WindowController.h"
#import "ViewController.h"
#import "InputViewController.h"
#import "ProgressViewController.h"

@interface WindowController () <NSTextFieldDelegate>

- (IBAction)onToolbarOpen:(id)sender;
- (IBAction)onToolbarSave:(id)sender;
- (IBAction)onToolbarSettings:(id)sender;
- (IBAction)onToolbarExport:(id)sender;
- (IBAction)onToolbarNewFolder:(id)sender;
- (IBAction)onToolbarDelete:(id)sender;
- (void)startExport;

@property (weak) IBOutlet NSSearchField *searchText;
@property (nonatomic, readonly, getter=getTree) TreeManager* tree;

@end

@implementation WindowController

- (void)windowDidLoad {
    [super windowDidLoad];
    
    // init title
    [self.window setTitleWithRepresentedFilename:self.tree.projectPath];
}

- (void)controlTextDidChange:(NSNotification *)n {
    if(n.object == self.searchText) {
        NSString* text = self.searchText.stringValue;
        text = [text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        ViewController* vc = (ViewController*)self.window.contentViewController;
        vc.filterKeyword = text;
    }
}

- (TreeManager*)getTree {
    ViewController* vc = (ViewController*)self.window.contentViewController;
    return vc.tree;
}

- (IBAction)onToolbarOpen:(id)sender {
    if(self.tree.dirty) {
        NSAlert* alert = [[NSAlert alloc] init];
        [alert setMessageText:@"Do you want to save current project?"];
        [alert addButtonWithTitle:@"Save"];
        [alert addButtonWithTitle:@"Discard"];
        [alert addButtonWithTitle:@"Cancel"];
        switch([alert runModal]) {
            case NSAlertFirstButtonReturn:
            {
                ViewController* vc = (ViewController*)[self.window contentViewController];
                NSSavePanel* saveDlg = [NSSavePanel savePanel];
                [saveDlg setCanCreateDirectories:YES];
                [saveDlg setShowsHiddenFiles:NO];
                [saveDlg setExtensionHidden:NO];
                [saveDlg setAllowedFileTypes:@[@"lpkproj"]];
                [saveDlg setNameFieldStringValue:[vc.tree.projectPath lastPathComponent]];
                if([saveDlg runModal] == NSModalResponseOK) {
                    NSString* filePath = [[saveDlg URL] path];
                    vc.tree.projectPath = filePath;
                    [vc.tree saveProject];
                    [self.window setTitleWithRepresentedFilename:self.tree.projectPath];
                }
                break;
            }
            case NSAlertThirdButtonReturn:
                return;
            default:
                break;
        }
    }
    
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg setAllowedFileTypes:@[@"lpkproj"]];
    [openDlg beginSheetModalForWindow:self.window completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            // Get an array containing the full filenames of all
            // files and directories selected.
            NSArray* urls = [openDlg URLs];
            NSString* filePath = [[urls objectAtIndex:0] path];
            self.tree.projectPath = filePath;
            [self.tree loadProject];
            [self.window setTitleWithRepresentedFilename:self.tree.projectPath];
            ViewController* vc = (ViewController*)self.window.contentViewController;
            [vc reloadFileOutline];
        }
    }];
}

- (IBAction)onToolbarSave:(id)sender {
    NSSavePanel* saveDlg = [NSSavePanel savePanel];
    [saveDlg setCanCreateDirectories:YES];
    [saveDlg setShowsHiddenFiles:NO];
    [saveDlg setExtensionHidden:NO];
    [saveDlg setAllowedFileTypes:@[@"lpkproj"]];
    [saveDlg setNameFieldStringValue:[self.tree.projectPath lastPathComponent]];
    [saveDlg beginSheetModalForWindow:self.window completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            NSString* filePath = [[saveDlg URL] path];
            self.tree.projectPath = filePath;
            [self.tree saveProject];
            [self.window setTitleWithRepresentedFilename:self.tree.projectPath];
        }
    }];
}

- (IBAction)onToolbarSettings:(id)sender {
}

- (IBAction)onToolbarExport:(id)sender {
    NSSavePanel* saveDlg = [NSSavePanel savePanel];
    [saveDlg setCanCreateDirectories:YES];
    [saveDlg setShowsHiddenFiles:NO];
    [saveDlg setExtensionHidden:NO];
    [saveDlg setAllowedFileTypes:@[@"lpk"]];
    if([@"" isEqualToString:self.tree.exportPath]) {
        NSString* projName = [[self.tree.projectPath lastPathComponent] stringByDeletingPathExtension];
        NSString* lpkName = [NSString stringWithFormat:@"%@.lpk", projName];
        self.tree.exportPath = [[self.tree.projectPath stringByDeletingLastPathComponent] stringByAppendingPathComponent:lpkName];
    }
    [saveDlg setNameFieldStringValue:[self.tree.exportPath lastPathComponent]];
    [saveDlg beginSheetModalForWindow:self.window completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            // save export path
            NSString* filePath = [[saveDlg URL] path];
            self.tree.exportPath = filePath;
            
            // export
            [self performSelector:@selector(startExport) withObject:nil afterDelay:0.7f];
        }
    }];
}

- (void)startExport {
    // start a progress
    NSStoryboard* sb = [NSStoryboard storyboardWithName:@"Main" bundle:nil];
    NSWindowController* progress = [sb instantiateControllerWithIdentifier:@"progress"];
    ProgressViewController* vc = (ProgressViewController*)progress.contentViewController;
    [self.window beginSheet:vc.view.window completionHandler:nil];
    
    // start export
    [self.tree exportLPK:vc];
}

- (IBAction)onToolbarNewFolder:(id)sender {
    NSStoryboard* sb = [NSStoryboard storyboardWithName:@"Main" bundle:nil];
    NSWindowController* input = [sb instantiateControllerWithIdentifier:@"input"];
    InputViewController* vc = (InputViewController*)input.contentViewController;
    vc.hintLabel.stringValue = @"Input new folder name";
    [self.window beginSheet:input.window completionHandler:^(NSModalResponse returnCode) {
        if(returnCode == NSModalResponseOK) {
            NSString* name = vc.inputText.stringValue;
            ViewController* mainVC = (ViewController*)self.contentViewController;
            LpkEntry* e = [mainVC getFirstSelectedItem];
            e = e ? (e.isDir ? e : e.parent) : self.tree.root;
            if([e hasChild:name]) {
                NSAlert* alert = [[NSAlert alloc] init];
                [alert setMessageText:[NSString stringWithFormat:@"The name \"%@\" already exists", name]];
                [alert beginSheetModalForWindow:self.window completionHandler:nil];
            } else {
                [self.tree newFolder:name toDir:e];
                [mainVC reloadFileOutline];
            }
        }
    }];
}

- (IBAction)onToolbarDelete:(id)sender {
    ViewController* vc = (ViewController*)self.window.contentViewController;
    [vc onDelete:sender];
}

@end
