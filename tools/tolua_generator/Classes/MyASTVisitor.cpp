//
//  MyASTVisitor.cpp
//  tolua_generator
//
//  Created by maruojie on 14/12/20.
//  Copyright (c) 2014年 luma. All rights reserved.
//

#include "MyASTVisitor.h"

void MyASTVisitor::debugOutputLoc(SourceLocation& loc) {
    SourceManager& srcMgr = m_ctx->getSourceManager();
    cout << "loc: " << srcMgr.getExpansionLineNumber(loc) << "," << srcMgr.getExpansionColumnNumber(loc) << endl;
}

SourceLocation MyASTVisitor::findLastRParenForPureVirtual(CXXMethodDecl* decl) {
    SourceManager& sm = m_ctx->getSourceManager();
    for(int i = 0; i >= -INT32_MAX; i--) {
        const char* buf = sm.getCharacterData(decl->getLocEnd().getLocWithOffset(i));
        if(buf[0] == ')') {
            return decl->getLocEnd().getLocWithOffset(i);
        }
    }
    return SourceLocation();
}

bool MyASTVisitor::VisitFunctionDecl(FunctionDecl* decl) {
    // remove block comment
    const RawComment* rc = m_ctx->getRawCommentForAnyRedecl(decl);
    if(rc) {
        m_rewriter.RemoveText(rc->getSourceRange());
    }
    
    // if not cpp method
    if(!isa<CXXMethodDecl>(decl)) {
        // remove body
        if (decl->hasBody()) {
            Stmt* funcBody = decl->getBody();
            m_rewriter.InsertText(funcBody->getLocEnd().getLocWithOffset(1), ";");
            m_rewriter.RemoveText(funcBody->getSourceRange());
        }
    }
    
    return true;
}

bool MyASTVisitor::VisitDecl(Decl* decl) {
    decl->dump();
    return true;
}

bool MyASTVisitor::VisitCXXMethodDecl(CXXMethodDecl* decl) {
    // if not public, remove
    AccessSpecifier as = decl->getAccess();
    if(as != AS_public) {
        SourceLocation endLoc = Lexer::findLocationAfterToken(decl->getLocEnd(), tok::semi, m_ctx->getSourceManager(), m_ctx->getLangOpts(), false);
        m_rewriter.RemoveText(SourceRange(decl->getLocStart(), endLoc));
    } else { // so it is public
        // remove body
        if (decl->hasBody()) {
            Stmt* funcBody = decl->getBody();
            m_rewriter.InsertText(funcBody->getLocEnd().getLocWithOffset(1), ";");
            m_rewriter.RemoveText(funcBody->getSourceRange());
        }
        
        // remove pure virtual = 0
        if(decl->isVirtual() && decl->isPure()) {
            SourceLocation rpLoc = findLastRParenForPureVirtual(decl);
            m_rewriter.RemoveText(SourceRange(rpLoc.getLocWithOffset(1), decl->getLocEnd()));
        }
    }
    
    return true;
}

bool MyASTVisitor::VisitCXXDestructorDecl(CXXDestructorDecl* decl) {
    SourceLocation endLoc = Lexer::findLocationAfterToken(decl->getLocEnd(), tok::semi, m_ctx->getSourceManager(), m_ctx->getLangOpts(), false);
    m_rewriter.RemoveText(SourceRange(decl->getLocStart(), endLoc));
    return true;
}

bool MyASTVisitor::VisitAccessSpecDecl(AccessSpecDecl* decl) {
    m_rewriter.RemoveText(decl->getSourceRange());
    return true;
}