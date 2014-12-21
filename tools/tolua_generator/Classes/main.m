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

static void preprocessSource(const char* path) {
    
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        if (argc != 2) {
            llvm::errs() << "Usage: rewritersample <filename>\n";
            return 1;
        }
        
        // preprocess source file, to remove something
        preprocessSource(argv[1]);
        
        // CompilerInstance will hold the instance of the Clang compiler for us,
        // managing the various objects needed to run the compiler.
        CompilerInstance compiler;
        compiler.createDiagnostics(NULL, false);
        DiagnosticsEngine& diagEngine = compiler.getDiagnostics();
        LangOptions& langOpt = compiler.getLangOpts();
        langOpt.CPlusPlus = 1;
        
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
        HeaderSearchOptions* hsOpt = new HeaderSearchOptions("/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS8.1.sdk");
        hsOpt->AddPath("/Users/maruojie/Projects/cocos2dx-classical/cocos2dx", frontend::Angled, false, true);
        hsOpt->AddPath("/Users/maruojie/Projects/cocos2dx-classical/cocos2dx/include", frontend::Angled, false, true);
        IntrusiveRefCntPtr<HeaderSearchOptions> hsoPtr(hsOpt);
        HeaderSearch hs(hsoPtr, srcMgr, diagEngine, langOpt, ti);
        ApplyHeaderSearchOptions(hs, *hsOpt, langOpt, ti->getTriple());
        
        // create preprocessor and set to compiler
        PreprocessorOptions* prepOpt = new PreprocessorOptions();
        IntrusiveRefCntPtr<PreprocessorOptions> poPtr(prepOpt);
        Preprocessor* prep = new Preprocessor(poPtr, diagEngine, langOpt, srcMgr, hs, compiler);
        compiler.setPreprocessor(prep);
        
        // Set the main file handled by the source manager to the input file.
        const FileEntry* FileIn = fileMgr.getFile(argv[1]);
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
        if(rewriteBuf)
            llvm::outs() << string(rewriteBuf->begin(), rewriteBuf->end());
    }
    return 0;
}
