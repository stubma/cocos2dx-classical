//
//  TreeManager.m
//  lpk
//
//  Created by maruojie on 15/2/16.
//  Copyright (c) 2015年 luma. All rights reserved.
//

#import "TreeManager.h"
#import "NSArray+Transform.h"

@implementation TreeManager

- (id)init {
    if(self = [super init]) {
        self.root = [[LpkEntry alloc] init];
        self.exportPath = [@"~/Documents/Untitled.lpk" stringByExpandingTildeInPath];
        self.projectPath = [@"~/Documents/Untitled.lpkproj" stringByExpandingTildeInPath];
        return self;
    }
    return nil;
}

- (void)addFiles:(NSArray*)paths toDir:(LpkEntry*)dir {
    // use root if dir is nil
    if(!dir) {
        dir = self.root;
    }
    
    // add every file, depends on it is folder or file
    for(NSString* path in paths) {
        LpkEntry* e = [[LpkEntry alloc] initWithPath:path];
        if(e) {
            // add to dir
            [dir addChild:e];
            
            // if it is dir also, add recursively
            if(e.isDir) {
                NSFileManager* fm = [NSFileManager defaultManager];
                NSArray* tmp = [fm contentsOfDirectoryAtPath:path error:nil];
                NSArray* subpaths = [tmp arrayByApplyingBlock:^id(id s) {
                    return [path stringByAppendingPathComponent:s];
                }];
                [self addFiles:subpaths toDir:e];
            }
        }
    }
    
    // sort
    [dir sortChildrenRecursively];
    
    // flag
    self.dirty = YES;
}

- (LpkEntry*)entryByKey:(NSString*)key {
    NSArray* parts = [key componentsSeparatedByString:@"/"];
    LpkEntry* e = self.root;
    for(NSString* name in parts) {
        if([@"" isEqualToString:name])
            continue;
        e = [e childByName:name];
        if(!e)
            break;
    }
    return e;
}

- (NSArray*)stripContainedKeys:(NSArray*)keys {
    // get folder entries
    NSArray* folders = [keys arrayByApplyingBlock:^id(id key) {
        LpkEntry* e = [self entryByKey:key];
        if(e && e.isDir) {
            return e;
        } else {
            return nil;
        }
    }];
    
    // remove file entries in folders
    return [keys arrayByApplyingBlock:^id(id key) {
        LpkEntry* e = [self entryByKey:key];
        if(e) {
            if(![e isContainedByAnyDir:folders]) {
                return e;
            }
        }
        
        return nil;
    }];
}

- (NSArray*)stripContainedEntries:(NSArray*)entries {
    // get folder entries
    NSArray* folders = [entries arrayByApplyingBlock:^id(id obj) {
        LpkEntry* e = (LpkEntry*)obj;
        if(e && e.isDir) {
            return e;
        } else {
            return nil;
        }
    }];
    
    // remove file entries in folders
    return [entries arrayByApplyingBlock:^id(id obj) {
        LpkEntry* e = (LpkEntry*)obj;
        if(e) {
            if(![e isContainedByAnyDir:folders]) {
                return e;
            }
        }
        
        return nil;
    }];
}

- (void)moveEntryByKeys:(NSArray*)keys toDir:(LpkEntry*)dir {
    // use root if dir is nil
    if(!dir) {
        dir = self.root;
    }
    
    // strip contained entries
    NSArray* ndupEntries = [self stripContainedKeys:keys];
    
    // move every entry
    NSMutableArray* affectedParents = [NSMutableArray array];
    for(LpkEntry* e in ndupEntries) {
        // detach entry from parent
        if(dir != e.parent && dir != e) {
            [affectedParents addObject:e.parent];
            [e removeFromParent];
            [dir addChild:e];
        }
    }
    
    // resort changed entry
    for(LpkEntry* e in affectedParents) {
        [e sortChildren];
    }
    
    // sort
    [dir sortChildren];
    
    // flag
    self.dirty = YES;
}

- (void)removeEntries:(NSArray*)entries {
    // strip contained entries
    NSArray* ndupEntries = [self stripContainedEntries:entries];
    
    // remove every entry
    for(LpkEntry* e in ndupEntries) {
        [e removeFromParent];
    }
    
    // flag
    self.dirty = YES;
}

- (void)newFolder:(NSString*)name toDir:(LpkEntry*)dir {
    // create entry
    LpkEntry* e = [[LpkEntry alloc] initWithFolderName:name];
    
    // use root if dir is nil
    if(!dir) {
        dir = self.root;
    }
    
    // add
    [dir addChild:e];
    
    // sort
    [dir sortChildren];
    
    // flag
    self.dirty = YES;
}

- (void)loadProject {
    NSDictionary* dict = [NSDictionary dictionaryWithContentsOfFile:self.projectPath];
    if(dict) {
        self.root = [LpkEntry decodeWithDictionary:dict];
        
        // flag
        self.dirty = NO;
    }
}

- (void)saveProject {
    NSError* err = nil;
    NSOutputStream* os = [NSOutputStream outputStreamToFileAtPath:self.projectPath append:NO];
    [os open];
    NSMutableDictionary* root = [NSMutableDictionary dictionary];
    [self.root encodeWithDictionary:root relativeTo:[self.projectPath stringByDeletingLastPathComponent]];
    if(![NSPropertyListSerialization writePropertyList:root
                                              toStream:os
                                                format:NSPropertyListXMLFormat_v1_0
                                               options:0
                                                 error:&err]) {
        NSAlert* alert = [[NSAlert alloc] init];
        [alert setMessageText:[err localizedDescription]];
        [alert beginSheetModalForWindow:[[NSApplication sharedApplication] mainWindow] completionHandler:nil];
    } else {
        self.dirty = NO;
    }
    [os close];
}

- (void)exportLPK {
    
}

- (void)rebuildFilterChildren:(NSString*)keyword {
    [self.root rebuildFilterChildren:keyword];
}

@end
