//
//  MyASTVisitor.h
//  tolua_generator
//
//  Created by maruojie on 14/12/20.
//  Copyright (c) 2014年 luma. All rights reserved.
//

#ifndef __tolua_generator__MyASTVisitor__
#define __tolua_generator__MyASTVisitor__

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
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "MyASTVisitor.h"

using namespace clang;
using namespace std;

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
private:
    Rewriter& m_rewriter;
    
public:
    MyASTVisitor(Rewriter& r)
    : m_rewriter(r) {
    }
    
    bool VisitStmt(Stmt* s);
    bool VisitType(Type* T);
    bool VisitFunctionDecl(FunctionDecl* f);
};

#endif /* defined(__tolua_generator__MyASTVisitor__) */
