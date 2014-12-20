//
//  MyASTVisitor.cpp
//  tolua_generator
//
//  Created by maruojie on 14/12/20.
//  Copyright (c) 2014年 luma. All rights reserved.
//

#include "MyASTVisitor.h"

bool MyASTVisitor::VisitStmt(Stmt* s) {
    // Only care about If statements.
    if (isa<IfStmt>(s)) {
        IfStmt *IfStatement = cast<IfStmt>(s);
        Stmt *Then = IfStatement->getThen();
        
        m_rewriter.InsertText(Then->getLocStart(),
                               "// the 'if' part\n",
                               true, true);
        
        Stmt *Else = IfStatement->getElse();
        if (Else)
            m_rewriter.InsertText(Else->getLocStart(),
                                  "// the 'else' part\n",
                                  true, true);
    }
    
    return true;
}

bool MyASTVisitor::VisitFunctionDecl(FunctionDecl* f) {
    // Only function definitions (with bodies), not declarations.
    if (f->hasBody()) {
        Stmt *FuncBody = f->getBody();
        
        // Type name as string
        QualType QT = f->getReturnType();
        string TypeStr = QT.getAsString();
        
        // Function name
        DeclarationName DeclName = f->getNameInfo().getName();
        string FuncName = DeclName.getAsString();
        
        // Add comment before
        stringstream SSBefore;
        SSBefore << "// Begin function " << FuncName << " returning "
        << TypeStr << "\n";
        SourceLocation ST = f->getSourceRange().getBegin();
        m_rewriter.InsertText(ST, SSBefore.str(), true, true);
        
        // And after
        stringstream SSAfter;
        SSAfter << "\n// End function " << FuncName << "\n";
        ST = FuncBody->getLocEnd().getLocWithOffset(1);
        m_rewriter.InsertText(ST, SSAfter.str(), true, true);
    }
    
    return true;
}