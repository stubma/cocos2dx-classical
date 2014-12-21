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

void MyASTVisitor::removeFunctionBody(FunctionDecl* decl) {
    if (decl->hasBody()) {
        Stmt* funcBody = decl->getBody();
        m_rewriter.InsertText(funcBody->getLocEnd().getLocWithOffset(1), ";");
        m_rewriter.RemoveText(funcBody->getSourceRange());
    }
}

void MyASTVisitor::removeFunction(FunctionDecl* decl) {
    SourceLocation endLoc = Lexer::findLocationAfterToken(decl->getLocEnd(), tok::semi, m_ctx->getSourceManager(), m_ctx->getLangOpts(), false);
    if(endLoc.isValid()) {
        m_rewriter.RemoveText(SourceRange(decl->getLocStart(), endLoc));
    } else {
        m_rewriter.RemoveText(decl->getSourceRange());
    }
}

bool MyASTVisitor::VisitFunctionDecl(FunctionDecl* decl) {
    // remove block comment
    const RawComment* rc = m_ctx->getRawCommentForAnyRedecl(decl);
    if(rc) {
        m_rewriter.RemoveText(rc->getSourceRange());
    }
    
    // if not cpp method
    if(!isa<CXXMethodDecl>(decl)) {
        // if static, remove
        // if extern, remove
        // for other, remove body
        if(decl->getStorageClass() == SC_Static || decl->getStorageClass() == SC_Extern) {
            removeFunction(decl);
        } else {
            removeFunctionBody(decl);
        }
    }
    
    return true;
}

bool MyASTVisitor::VisitTranslationUnitDecl(TranslationUnitDecl* decl) {
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
        // if destructor, remove
        // if not, remove body
        // if pure virtual, remove = 0
        if(isa<CXXDestructorDecl>(decl)) {
            removeFunction(decl);
        } else {
            removeFunctionBody(decl);
            if(decl->isVirtual() && decl->isPure()) {
                SourceLocation rpLoc = findLastRParenForPureVirtual(decl);
                m_rewriter.RemoveText(SourceRange(rpLoc.getLocWithOffset(1), decl->getLocEnd()));
            }
        }
    }
    
    return true;
}

bool MyASTVisitor::VisitAccessSpecDecl(AccessSpecDecl* decl) {
    m_rewriter.RemoveText(decl->getSourceRange());
    return true;
}

bool MyASTVisitor::VisitFieldDecl(FieldDecl* decl) {
    // remove non-public field
    AccessSpecifier as = decl->getAccess();
    if(as != AS_public) {
        SourceLocation endLoc = Lexer::findLocationAfterToken(decl->getLocEnd(), tok::semi, m_ctx->getSourceManager(), m_ctx->getLangOpts(), false);
        m_rewriter.RemoveText(SourceRange(decl->getLocStart(), endLoc));
    }
    
    return true;
}

bool MyASTVisitor::VisitVarDecl(VarDecl* decl) {
    // remove static local
    if(decl->isFileVarDecl() && decl->getStorageClass() == SC_Static) {
        SourceLocation endLoc = Lexer::findLocationAfterToken(decl->getLocEnd(), tok::semi, m_ctx->getSourceManager(), m_ctx->getLangOpts(), false);
        m_rewriter.RemoveText(SourceRange(decl->getLocStart(), endLoc));
    }
    
    return true;
}

bool MyASTVisitor::VisitNamespaceDecl(NamespaceDecl* decl) {
    m_rewriter.RemoveText(decl->getRBraceLoc(), 1);
    SourceLocation endLoc = Lexer::findLocationAfterToken(decl->getLocation(), tok::l_brace, m_ctx->getSourceManager(), m_ctx->getLangOpts(), false);
    m_rewriter.RemoveText(SourceRange(decl->getLocStart(), endLoc));
    return true;
}