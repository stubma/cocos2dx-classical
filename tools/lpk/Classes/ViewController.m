//
//  ViewController.m
//  lpk
//
//  Created by maruojie on 15/2/15.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "ViewController.h"
#import "NSOutlineView+State.h"
#import "AddBranchViewController.h"
#import "DefaultViewerViewController.h"

#define DRAG_TYPE_LPK_ENTRY @"_dt_lpk_entry"

@interface ViewController () <NSSplitViewDelegate, NSOutlineViewDataSource, NSOutlineViewDelegate, NSTableViewDataSource, NSTableViewDelegate>

@property (weak) IBOutlet CNSplitView *hSplitView;
@property (weak) IBOutlet CNSplitView *vSplitView;
@property (weak) IBOutlet NSOutlineView *fileOutlineView;
@property (weak) IBOutlet NSTableView *infoTableView;
@property (weak) IBOutlet NSView *viewerContainer;
@property (nonatomic, assign) BOOL hasFilter;
@property (nonatomic, strong) NSArray* expandedItems;
@property (nonatomic, strong) ViewerViewController* viewer;

- (void)updateViewer;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // create tree manager
    self.tree = [[TreeManager alloc] init];
    
    // init file outline view
    self.filterKeyword = @"";
    [self.fileOutlineView reloadData];
    [self.fileOutlineView registerForDraggedTypes:@[NSFilenamesPboardType, NSStringPboardType]];
    
    // init info table view
    [self.infoTableView registerForDraggedTypes:@[NSFilenamesPboardType]];
}

- (void)reloadFileOutline {
    [self.fileOutlineView reloadData];
    
    // ensure filter works
    self.filterKeyword = self.filterKeyword;
}

- (void)reloadInfoTable {
    [self.infoTableView reloadData];
}

- (void)setFilterKeyword:(NSString*)keyword {
    // old filter state
    BOOL oldHasFilter = ![@"" isEqualToString:self.filterKeyword];
    
    // save keyword
    _filterKeyword = keyword;
    self.hasFilter = ![@"" isEqualToString:self.filterKeyword];
    
    // rebuild filtered children list
    if(self.hasFilter) {
        [self.tree rebuildFilterChildren:self.filterKeyword];
    }
    
    // depends on state
    if(!oldHasFilter && self.hasFilter) {
        self.expandedItems = [self.fileOutlineView expandedItems];
        [self.fileOutlineView reloadData];
        [self.fileOutlineView expandItem:nil expandChildren:YES];
    } else if(oldHasFilter && !self.hasFilter) {
        [self.fileOutlineView reloadData];
        [self.fileOutlineView collapseItem:nil collapseChildren:YES];
        [self.fileOutlineView expandItems:self.expandedItems];
    } else if(self.hasFilter) {
        [self.fileOutlineView reloadData];
        [self.fileOutlineView expandItem:nil expandChildren:YES];
    }
    
    // workaround to make scrollbar visible
    [self.fileOutlineView scrollRowToVisible:0];
}

- (void)updateViewer {
    // remove old viewer
    if(self.viewer) {
        [self.viewer.view removeFromSuperview];
        self.viewer = nil;
    }
    
    // set new viewer
    LpkEntry* e = [self getFirstSelectedItem];
    if(e && !e.isDir) {
        LpkBranchEntry* b = self.infoTableView.selectedRow >= 0 ? [e.branches objectAtIndex:self.infoTableView.selectedRow] : [e getFirstBranch];
        NSString* extension = [b.realPath pathExtension];
        if(![b.realPath isAbsolutePath]) {
            b.realPath = [[[self.tree.projectPath stringByDeletingLastPathComponent] stringByAppendingPathComponent:b.realPath] stringByStandardizingPath];
        }
        
        // instantiate viewer
        NSStoryboard* sb = [NSStoryboard storyboardWithName:@"Main" bundle:nil];
        ViewerViewController* vc = nil;
        if([@"png" isEqual:extension] || [@"jpg" isEqual:extension] || [@"jpeg" isEqual:extension]) {
            vc = (ViewerViewController*)[sb instantiateControllerWithIdentifier:@"image_viewer"];
        } else {
            vc = (ViewerViewController*)[sb instantiateControllerWithIdentifier:@"default_viewer"];
        }
        
        // load view
        [vc loadView];
        
        // set branch
        vc.branch = b;
        
        // add to container
        self.viewer = vc;
        [self.viewerContainer addSubview:vc.view];
        
        // add constraints
        vc.view.translatesAutoresizingMaskIntoConstraints = NO;
        NSMutableArray* constraints = [NSMutableArray array];
        [constraints addObjectsFromArray:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[viewer]-0-|"
                                                                                 options:0
                                                                                 metrics:nil
                                                                                   views:@{ @"viewer" : vc.view }]];
        [constraints addObjectsFromArray:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[viewer]-0-|"
                                                                                 options:0
                                                                                 metrics:nil
                                                                                   views:@{ @"viewer" : vc.view }]];
        [self.viewerContainer addConstraints:constraints];
    }
}

#pragma mark -
#pragma mark splitview delegate

- (CGFloat)splitView:(NSSplitView *)splitView constrainMinCoordinate:(CGFloat)proposedMin ofSubviewAt:(NSInteger)dividerIndex {
    if(splitView == self.hSplitView) {
        return self.hSplitView.frame.size.height * 0.2f;
    } else {
        return self.vSplitView.frame.size.width * 0.1f;
    }
}

- (CGFloat)splitView:(NSSplitView *)splitView constrainMaxCoordinate:(CGFloat)proposedMax ofSubviewAt:(NSInteger)dividerIndex {
    if(splitView == self.hSplitView) {
        return self.hSplitView.frame.size.height * 0.9f;
    } else {
        return self.vSplitView.frame.size.width * 0.9f;
    }
}

#pragma mark -
#pragma mark outline data source

- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item {
    if(item) {
        LpkEntry* e = (LpkEntry*)item;
        return self.hasFilter ? [e.filteredChildren count] : [e.children count];
    } else {
        return 1;
    }
}

- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item {
    if(item) {
        LpkEntry* e = (LpkEntry*)item;
        return self.hasFilter ? [e.filteredChildren objectAtIndex:index] : [e.children objectAtIndex:index];
    } else {
        return self.tree.root;
    }
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item {
    LpkEntry* e = (LpkEntry*)item;
    return e && e.isDir;
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item {
    LpkEntry* e = (LpkEntry*)item;
    if([@"name" isEqualToString:tableColumn.identifier]) {
        return e.name;
    } else if([@"size" isEqualToString:tableColumn.identifier]) {
        return [NSNumber numberWithUnsignedInt:e.totalSize];
    } else {
        return nil;
    }
}

- (NSDragOperation)outlineView:(NSOutlineView *)outlineView
                  validateDrop:(id<NSDraggingInfo>)info
                  proposedItem:(id)item
            proposedChildIndex:(NSInteger)index {
    // check operation
    NSPasteboard* pboard = [info draggingPasteboard];
    if([[pboard types] containsObject:NSFilenamesPboardType]) {
        return NSDragOperationCopy;
    } else if([[pboard types] containsObject:NSStringPboardType]) {
        return NSDragOperationMove;
    } else {
        return NSDragOperationNone;
    }
}

- (BOOL)outlineView:(NSOutlineView *)outlineView
         acceptDrop:(id<NSDraggingInfo>)info
               item:(id)item
         childIndex:(NSInteger)index {
    NSPasteboard* pboard = [info draggingPasteboard];
    if([[pboard types] containsObject:NSFilenamesPboardType]) {
        // get add root
        LpkEntry* e = (LpkEntry*)item;
        e = e ? (e.isDir ? e : e.parent) : self.tree.root;
        
        // validate names
        NSArray *files = [pboard propertyListForType:NSFilenamesPboardType];
        for(NSString* path in files) {
            NSString* name = [path lastPathComponent];
            if([e hasChild:name]) {
                NSAlert* alert = [[NSAlert alloc] init];
                [alert setMessageText:[NSString stringWithFormat:@"\"%@\" already contains child whose name is \"%@\"", e.name, name]];
                [alert beginSheetModalForWindow:self.view.window completionHandler:nil];
                return NO;
            }
        }
        
        // add files and reload outline
        [self.tree addFiles:files toDir:e];
        [self.fileOutlineView reloadData];
    } else if([[pboard types] containsObject:NSStringPboardType]) {
        // get keys
        NSArray* keys = [[pboard stringForType:NSStringPboardType] componentsSeparatedByCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
        
        // get root
        LpkEntry* e = (LpkEntry*)item;
        e = e ? (e.isDir ? e : e.parent) : self.tree.root;
        
        // strip contained entries
        NSArray* ndupEntries = [self.tree stripContainedKeys:keys];
        
        // validate names
        for(LpkEntry* c in ndupEntries) {
            if([e hasChild:c.name]) {
                NSAlert* alert = [[NSAlert alloc] init];
                [alert setMessageText:[NSString stringWithFormat:@"\"%@\" already contains child whose name is \"%@\"", e.name, c.name]];
                [alert beginSheetModalForWindow:self.view.window completionHandler:nil];
                return NO;
            }
        }
        
        // move and reload
        [self.tree moveEntryByKeys:keys toDir:e];
        [self.fileOutlineView reloadData];
    }
    
    // keep filter ok
    self.filterKeyword = self.filterKeyword;
    
    return YES;
}

- (id<NSPasteboardWriting>)outlineView:(NSOutlineView *)outlineView
               pasteboardWriterForItem:(id)item {
    // don't allow drag root
    LpkEntry* e = (LpkEntry*)item;
    return e.parent ? e.key : nil;
}

- (void)outlineView:(NSOutlineView *)outlineView
     setObjectValue:(id)object
     forTableColumn:(NSTableColumn *)tableColumn
             byItem:(id)item {
    // get entry
    LpkEntry* e = (LpkEntry*)item;
    
    // can't rename root
    if(!e.parent)
        return;
    
    // set new name
    if([@"name" isEqualToString:tableColumn.identifier]) {
        NSString* newName = (NSString*)object;
        if([e.parent hasChild:newName]) {
            NSAlert* alert = [[NSAlert alloc] init];
            [alert setMessageText:[NSString stringWithFormat:@"The name \"%@\" already exists", newName]];
            [alert beginSheetModalForWindow:self.view.window completionHandler:nil];
        } else {
            e.name = newName;
            [e.parent sortChildren];
            [outlineView reloadData];
        }
    }
    
    // keep filter ok
    self.filterKeyword = self.filterKeyword;
}

#pragma mark -
#pragma mark outline delegate

- (IBAction)onDelete:(id)sender {
    NSIndexSet* set = [self.fileOutlineView selectedRowIndexes];
    NSMutableArray* entries = [NSMutableArray array];
    [set enumerateIndexesUsingBlock:^(NSUInteger idx, BOOL *stop) {
        LpkEntry* e = (LpkEntry*)[self.fileOutlineView itemAtRow:idx];
        [entries addObject:e];
    }];
    [self.tree removeEntries:entries];
    [self.fileOutlineView reloadData];
    [self.fileOutlineView deselectAll:self];
    
    // keep filter ok
    self.filterKeyword = self.filterKeyword;
}

- (LpkEntry*)getFirstSelectedItem {
    NSIndexSet* set = [self.fileOutlineView selectedRowIndexes];
    LpkEntry* e = (LpkEntry*)[self.fileOutlineView itemAtRow:set.firstIndex];
    return e;
}

- (void)outlineViewSelectionDidChange:(NSNotification *)notificatio {
    [self.infoTableView reloadData];
    [self updateViewer];
}

#pragma mark -
#pragma mark tableview data source

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    LpkEntry* e = [self getFirstSelectedItem];
    if(!e || e.isDir) {
        return 0;
    } else {
        return [e.branches count];
    }
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    LpkEntry* e = [self getFirstSelectedItem];
    return [e.branches objectAtIndex:row];
}

- (NSDragOperation)tableView:(NSTableView *)aTableView
                validateDrop:(id<NSDraggingInfo>)info
                 proposedRow:(NSInteger)row
       proposedDropOperation:(NSTableViewDropOperation)operation {
    // if no file selected in outline view, no drop allowed
    LpkEntry* e = [self getFirstSelectedItem];
    if(!e || e.isDir)
        return NSDragOperationNone;
    
    // check operation
    NSPasteboard* pboard = [info draggingPasteboard];
    if([[pboard types] containsObject:NSFilenamesPboardType]) {
        return NSDragOperationCopy;
    } else {
        return NSDragOperationNone;
    }
}

- (BOOL)tableView:(NSTableView *)aTableView
       acceptDrop:(id<NSDraggingInfo>)info
              row:(NSInteger)row
    dropOperation:(NSTableViewDropOperation)operation {
    NSPasteboard* pboard = [info draggingPasteboard];
    if([[pboard types] containsObject:NSFilenamesPboardType]) {
        // get first file
        NSArray *files = [pboard propertyListForType:NSFilenamesPboardType];
        NSString* firstFile = [files objectAtIndex:0];
        
        // show sheet for this drop
        LpkEntry* trunk = [self getFirstSelectedItem];
        NSStoryboard* sb = [NSStoryboard storyboardWithName:@"Main" bundle:nil];
        NSWindowController* add = [sb instantiateControllerWithIdentifier:@"add_branch"];
        AddBranchViewController* vc = (AddBranchViewController*)add.contentViewController;
        vc.entry = trunk;
        vc.filePath = firstFile;
        [self.view.window beginSheet:add.window completionHandler:^(NSModalResponse returnCode) {
            if(returnCode == NSModalResponseOK) {
                // create new branch
                LpkBranchEntry* newb = [[LpkBranchEntry alloc] initWithPath:vc.filePath forTrunk:trunk];
                
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
                [trunk.branches addObject:newb];
                
                // flag dirty and reload info table
                self.tree.dirty = YES;
                [self reloadInfoTable];
            }
        }];
    }
    
    return YES;
}

@end
