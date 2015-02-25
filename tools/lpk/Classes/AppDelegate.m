//
//  AppDelegate.m
//  lpk
//
//  Created by maruojie on 15/2/15.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    initConsts();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender {
    NSWindow* window = [sender mainWindow];
    if([@"main_window" isEqualToString:window.identifier]) {
        ViewController* vc = (ViewController*)[window contentViewController];
        if(vc.tree.dirty) {
            NSAlert* alert = [[NSAlert alloc] init];
            [alert setMessageText:@"Do you want to save current project?"];
            [alert addButtonWithTitle:@"Save"];
            [alert addButtonWithTitle:@"Discard"];
            [alert addButtonWithTitle:@"Cancel"];
            NSApplicationTerminateReply reply = NSTerminateCancel;
            switch([alert runModal]) {
                case NSAlertFirstButtonReturn:
                {
                    ViewController* vc = (ViewController*)[[sender mainWindow] contentViewController];
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
                        reply = NSTerminateNow;
                    } else {
                        reply = NSTerminateCancel;
                    }
                    break;
                }
                case NSAlertThirdButtonReturn:
                    reply = NSTerminateCancel;
                    break;
                default:
                    reply = NSTerminateNow;
                    break;
            }
            return reply;
        } else {
            return NSTerminateNow;
        }
    } else {
        return NSTerminateCancel;
    }
}

@end
