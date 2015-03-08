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
#import "SettingsViewController.h"
#import "SettingsWindowController.h"
#include "ExtractViewController.h"

@interface WindowController () <NSTextFieldDelegate>

@property (nonatomic, assign) BOOL patchAfterExport;

- (IBAction)onToolbarOpen:(id)sender;
- (IBAction)onToolbarSave:(id)sender;
- (IBAction)onToolbarExport:(id)sender;
- (IBAction)onToolbarNewFolder:(id)sender;
- (IBAction)onToolbarDelete:(id)sender;
- (IBAction)onToolbarPatchLPK:(id)sender;
- (IBAction)onToolbarInspectLPK:(id)sender;
- (IBAction)onToolbarNewProject:(id)sender;
- (IBAction)onToolbarExtractFile:(id)sender;
- (void)startExport;
- (void)startPatch;

@property (weak) IBOutlet NSSearchField *searchText;

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

- (void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
    if([@"settings" isEqualToString:segue.identifier]) {
        SettingsWindowController* dstWindow = (SettingsWindowController*)segue.destinationController;
        dstWindow.tree = self.tree;
    }
    [super prepareForSegue:segue sender:sender];
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
            self.tree.exportPath = @"";
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

- (IBAction)onToolbarExport:(id)sender {
    self.patchAfterExport = NO;
    [self startExport];
}

- (void)startExport {
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
            
            // start a progress
            NSStoryboard* sb = [NSStoryboard storyboardWithName:@"Main" bundle:nil];
            NSWindowController* progress = [sb instantiateControllerWithIdentifier:@"progress"];
            ProgressViewController* vc = (ProgressViewController*)progress.contentViewController;
            [self.window beginSheet:vc.view.window completionHandler:nil];
            
            // start export
            [self.tree performSelectorInBackground:@selector(exportLPK:) withObject:vc];
            
            // patch
            if(self.patchAfterExport) {
                [self startPatch];
            }
        }
    }];
}

- (void)startPatch {
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:@"Patch this LPK to selected LPK"];
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg setAllowedFileTypes:@[@"lpk"]];
    [openDlg beginSheetModalForWindow:self.window completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            // get source path
            NSArray* urls = [openDlg URLs];
            NSString* filePath = [[urls objectAtIndex:0] path];
            
            // backup
            NSFileManager* fm = [NSFileManager defaultManager];
            NSString* bakPath = [[filePath stringByDeletingPathExtension] stringByAppendingString:@"_bak.lpk"];
            [fm copyItemAtPath:filePath toPath:bakPath error:nil];
            
            // open source lpk to be patched
            lpk_file lpk;
            int result = lpk_open_file(&lpk, [filePath cStringUsingEncoding:NSUTF8StringEncoding]);
            if(result != 0) {
                NSLog(@"lpk_open_file, open source error: %d", result);
                return;
            }
            
            // open patch lpk
            lpk_file patch;
            result = lpk_open_file(&patch, [self.tree.exportPath cStringUsingEncoding:NSUTF8StringEncoding]);
            if(result != 0) {
                NSLog(@"lpk_open_file, open patch error: %d", result);
                return;
            }
            
            // patch
            lpk_apply_patch(&lpk, &patch);

            // debug output
            lpk_debug_output(&lpk);
            
            // close file
            lpk_close_file(&lpk);
            lpk_close_file(&patch);
        }
    }];
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

- (IBAction)onToolbarPatchLPK:(id)sender {
    self.patchAfterExport = YES;
    NSFileManager* fm = [NSFileManager defaultManager];
    if([@"" isEqualToString:self.tree.exportPath] || ![fm fileExistsAtPath:self.tree.exportPath]) {
        [self startExport];
    } else {
        [self startPatch];
    }
}

- (IBAction)onToolbarInspectLPK:(id)sender {
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg setAllowedFileTypes:@[@"lpk"]];
    [openDlg beginSheetModalForWindow:self.window completionHandler:^(NSInteger result) {
        if (result == NSModalResponseOK) {
            // Get an array containing the full filenames of all
            // files and directories selected.
            NSArray* urls = [openDlg URLs];
            NSString* filePath = [[urls objectAtIndex:0] path];
            lpk_file lpk;
            int result = lpk_open_file(&lpk, [filePath cStringUsingEncoding:NSUTF8StringEncoding]);
            if(result != 0) {
                NSLog(@"lpk_open_file, error: %d", result);
                return;
            }
            
            // debug output
            lpk_debug_output(&lpk);
            
            // close file
            lpk_close_file(&lpk);
        }
    }];
}

- (IBAction)onToolbarNewProject:(id)sender {
    // save current one if dirty
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
    
    // re-create tree
    ViewController* vc = (ViewController*)self.window.contentViewController;
    vc.tree = [[TreeManager alloc] init];
    [vc reloadFileOutline];
    [self.window setTitleWithRepresentedFilename:vc.tree.projectPath];
}

- (IBAction)onToolbarExtractFile:(id)sender {
    NSStoryboard* sb = [NSStoryboard storyboardWithName:@"Main" bundle:nil];
    NSWindowController* input = [sb instantiateControllerWithIdentifier:@"extract"];
    ExtractViewController* vc = (ExtractViewController*)input.contentViewController;
    [self.window beginSheet:input.window completionHandler:^(NSModalResponse returnCode) {
        if(returnCode == NSModalResponseOK) {
        }
    }];
}

@end