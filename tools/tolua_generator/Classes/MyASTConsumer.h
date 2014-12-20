//
//  MyASTConsumer.h
//  tolua_generator
//
//  Created by maruojie on 14/12/20.
//  Copyright (c) 2014年 luma. All rights reserved.
//

#ifndef __tolua_generator__MyASTConsumer__
#define __tolua_generator__MyASTConsumer__

#include <cstdio>
#include <string>
#include <sstream>

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
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "MyASTVisitor.h"

using namespace clang;
using namespace std;

class MyASTConsumer : public ASTConsumer {
private:
    MyASTVisitor Visitor;
    
public:
    MyASTConsumer(Rewriter& R)
    : Visitor(R) {
    }
    
    // Override the method that gets called for each parsed top-level
    // declaration.
    virtual bool HandleTopLevelDecl(DeclGroupRef DR) {
        for (DeclGroupRef::iterator b = DR.begin(), e = DR.end();
             b != e; ++b)
            // Traverse the declaration using our AST visitor.
            Visitor.TraverseDecl(*b);
        return true;
    }
};

#endif /* defined(__tolua_generator__MyASTConsumer__) */
