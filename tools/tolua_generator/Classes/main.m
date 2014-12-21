//
//  main.m
//  tolua_generator
//
//  Created by maruojie on 14/12/20.
//  Copyright (c) 2014年 luma. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Rewrite/FrontEnd/Rewriters.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Lex/HeaderSearchOptions.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/ModuleLoader.h"
#include "clang/FrontEnd/Utils.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "MyASTConsumer.h"

using namespace clang;
using namespace std;

static void preprocessSource(NSString* path) {
    NSString* fileContent = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    
    // remove CC_DLL, CC_EX_DLL
    fileContent = [fileContent stringByReplacingOccurrencesOfString:@"CC_DLL" withString:@""];
    fileContent = [fileContent stringByReplacingOccurrencesOfString:@"CC_EX_DLL" withString:@""];
    
    // remove namespace macros
    fileContent = [fileContent stringByReplacingOccurrencesOfString:@"NS_CC_BEGIN" withString:@""];
    fileContent = [fileContent stringByReplacingOccurrencesOfString:@"NS_CC_END" withString:@""];
    fileContent = [fileContent stringByReplacingOccurrencesOfString:@"NS_CC_EXT_BEGIN" withString:@""];
    fileContent = [fileContent stringByReplacingOccurrencesOfString:@"NS_CC_EXT_END" withString:@""];
    fileContent = [fileContent stringByReplacingOccurrencesOfString:@"NS_TIMELINE_BEGIN" withString:@""];
    fileContent = [fileContent stringByReplacingOccurrencesOfString:@"NS_TIMELINE_END" withString:@""];
    NSRegularExpression* regExp = [NSRegularExpression regularExpressionWithPattern:@"USING_NS_CC(\\s*);"
                                                                            options:0
                                                                              error:nil];
    fileContent = [regExp stringByReplacingMatchesInString:fileContent
                                                   options:0
                                                     range:NSMakeRange(0, [fileContent length])
                                              withTemplate:@""];
    
    // remove #include
    regExp = [NSRegularExpression regularExpressionWithPattern:@"#include (.*)"
                                                       options:0
                                                         error:nil];
    fileContent = [regExp stringByReplacingMatchesInString:fileContent
                                                   options:0
                                                     range:NSMakeRange(0, [fileContent length])
                                              withTemplate:@""];
    
    // remove first #ifndef xxx and related
    regExp = [NSRegularExpression regularExpressionWithPattern:@"#ifndef(\\s+)__(.*)__"
                                                       options:0
                                                         error:nil];
    NSTextCheckingResult* firstMatch = [regExp firstMatchInString:fileContent
                                                          options:0
                                                            range:NSMakeRange(0, [fileContent length])];
    if([firstMatch range].location == NSNotFound) {
        NSLog(@"!!!!!!!! file %@ doesn't have proper exclusive directive, fix it!!!!!!!!", path);
    } else {
        NSString* macro = [fileContent substringWithRange:[firstMatch rangeAtIndex:2]];
        
        // remove ifndef
        NSString* pattern = [NSString stringWithFormat:@"#ifndef(\\s+)__%@__", macro];
        regExp = [NSRegularExpression regularExpressionWithPattern:pattern
                                                           options:0
                                                             error:nil];
        fileContent = [regExp stringByReplacingMatchesInString:fileContent
                                                       options:0
                                                         range:NSMakeRange(0, [fileContent length])
                                                  withTemplate:@""];
        
        // remove define
        pattern = [NSString stringWithFormat:@"#define(\\s+)__%@__", macro];
        regExp = [NSRegularExpression regularExpressionWithPattern:pattern
                                                           options:0
                                                             error:nil];
        firstMatch = [regExp firstMatchInString:fileContent
                                        options:0
                                          range:NSMakeRange(0, [fileContent length])];
        if([firstMatch range].location == NSNotFound) {
            NSLog(@"!!!!!!!! file %@ doesn't have proper exclusive directive, fix it!!!!!!!!", path);
        } else {
            fileContent = [regExp stringByReplacingMatchesInString:fileContent
                                                           options:0
                                                             range:NSMakeRange(0, [fileContent length])
                                                      withTemplate:@""];
        }
        
        // remove endif
        pattern = [NSString stringWithFormat:@"#endif(\\s+)//(\\s+)__%@__", macro];
        regExp = [NSRegularExpression regularExpressionWithPattern:pattern
                                                           options:0
                                                             error:nil];
        firstMatch = [regExp firstMatchInString:fileContent
                                        options:0
                                          range:NSMakeRange(0, [fileContent length])];
        if([firstMatch range].location == NSNotFound) {
            NSLog(@"!!!!!!!! file %@ doesn't have proper exclusive directive, fix it!!!!!!!!", path);
        } else {
            fileContent = [regExp stringByReplacingMatchesInString:fileContent
                                                           options:0
                                                             range:NSMakeRange(0, [fileContent length])
                                                      withTemplate:@""];
        }
    }
    
    // remove #define
    regExp = [NSRegularExpression regularExpressionWithPattern:@"#define (.*)"
                                                       options:0
                                                         error:nil];
    fileContent = [regExp stringByReplacingMatchesInString:fileContent
                                                   options:0
                                                     range:NSMakeRange(0, [fileContent length])
                                              withTemplate:@""];
    
    // CREATE_FUNC
    regExp = [NSRegularExpression regularExpressionWithPattern:@"CREATE_FUNC\\((.*)\\)"
                                                       options:0
                                                         error:nil];
    fileContent = [regExp stringByReplacingMatchesInString:fileContent
                                                   options:0
                                                     range:NSMakeRange(0, [fileContent length])
                                              withTemplate:@"static $1* create();"];
    
    // save modified source to same path
    NSData* data = [NSData dataWithBytes:[fileContent cStringUsingEncoding:NSUTF8StringEncoding]
                                  length:[fileContent lengthOfBytesUsingEncoding:NSUTF8StringEncoding]];
    [data writeToFile:path atomically:NO];
}

static void processSource(NSString* path) {
    // CompilerInstance will hold the instance of the Clang compiler for us,
    // managing the various objects needed to run the compiler.
    CompilerInstance compiler;
    compiler.createDiagnostics(NULL, false);
    DiagnosticsEngine& diagEngine = compiler.getDiagnostics();
    LangOptions& langOpt = compiler.getLangOpts();
    CompilerInvocation::setLangDefaults(langOpt, IK_CXX);
    
    // Initialize target info with the default triple for our platform.
    TargetOptions* to = new TargetOptions();
    to->Triple = llvm::sys::getDefaultTargetTriple();
    shared_ptr<TargetOptions> spTO(to);
    TargetInfo* ti = TargetInfo::CreateTargetInfo(diagEngine, spTO);
    compiler.setTarget(ti);
    
    // file manager
    compiler.createFileManager();
    FileManager& fileMgr = compiler.getFileManager();
    
    // source manager
    compiler.createSourceManager(fileMgr);
    SourceManager& srcMgr = compiler.getSourceManager();
    
    // header search options
    HeaderSearchOptions* hsOpt = new HeaderSearchOptions();
    IntrusiveRefCntPtr<HeaderSearchOptions> hsoPtr(hsOpt);
    HeaderSearch hs(hsoPtr, srcMgr, diagEngine, langOpt, ti);
    ApplyHeaderSearchOptions(hs, *hsOpt, langOpt, ti->getTriple());
    
    // create preprocessor and set to compiler
    PreprocessorOptions* prepOpt = new PreprocessorOptions();
    IntrusiveRefCntPtr<PreprocessorOptions> poPtr(prepOpt);
    Preprocessor* prep = new Preprocessor(poPtr, diagEngine, langOpt, srcMgr, hs, compiler);
    compiler.setPreprocessor(prep);
    
    // Set the main file handled by the source manager to the input file.
    const FileEntry* FileIn = fileMgr.getFile([path cStringUsingEncoding:NSUTF8StringEncoding]);
    srcMgr.setMainFileID(srcMgr.createFileID(FileIn, SourceLocation(), SrcMgr::C_User));
    
    // create ast context
    compiler.createASTContext();
    diagEngine.setClient(new IgnoringDiagConsumer());
    compiler.getDiagnosticClient().BeginSourceFile(langOpt, prep);
    
    // Create an AST consumer instance which is going to get called by ParseAST.
    Rewriter rewriter;
    rewriter.setSourceMgr(srcMgr, langOpt);
    MyASTConsumer consumer(rewriter);
    
    // Parse the file to AST, registering our consumer as the AST consumer.
    ParseAST(*prep, &consumer, compiler.getASTContext());
    
    // At this point the rewriter's buffer should be full with the rewritten
    // file contents.
    const RewriteBuffer* rewriteBuf = rewriter.getRewriteBufferFor(srcMgr.getMainFileID());
    if(rewriteBuf) {
        string tolua(rewriteBuf->begin(), rewriteBuf->end());
        NSLog(@"tolua result: %s", tolua.c_str());
        
        // save to tolua file
        NSData* data = [NSData dataWithBytes:tolua.c_str() length:tolua.length()];
        NSString* filenameWithoutExt = [path stringByDeletingPathExtension];
        NSString* filenameToLua = [NSString stringWithFormat:@"%@.tolua", filenameWithoutExt];
        [data writeToFile:filenameToLua atomically:NO];
    }
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        if (argc != 2) {
            NSLog(@"Usage: rewritersample <filename>\n");
            return 1;
        }
        
        // check path is folder or file, if file, process it
        // if folder, process files in it and in its sub folders
        // source file will be preprocessed because we need remove something and I don't how to do it with clang
        NSString* path = [NSString stringWithUTF8String:argv[1]];
        path = [path stringByExpandingTildeInPath];
        NSFileManager* fm = [NSFileManager defaultManager];
        BOOL dir;
        if([fm fileExistsAtPath:path isDirectory:&dir]) {
            if(dir) {
                // find all header files, and process them
                NSArray* subpaths = [fm subpathsOfDirectoryAtPath:path error:nil];
                for(NSString* subpath in subpaths) {
                    NSString* subFullPath = [path stringByAppendingPathComponent:subpath];
                    [fm fileExistsAtPath:subFullPath isDirectory:&dir];
                    if(!dir) {
                        NSString* ext = [subpath pathExtension];
                        if([@"h" isEqualToString:ext]) {
                            preprocessSource(subFullPath);
                            processSource(subFullPath);
                        }
                    }
                }
            } else {
                preprocessSource(path);
                processSource(path);
            }
        } else {
            NSLog(@"No file or directory found in %@", path);
        }
    }
    return 0;
}
