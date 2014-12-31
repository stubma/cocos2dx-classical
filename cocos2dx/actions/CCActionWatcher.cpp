//
//  CCActionWatcher.cpp
//  cocos2dx
//
//  Created on 14/12/31.
//  Copyright (c) 2014年 cocos2d-x. All rights reserved.
//

#include "CCActionWatcher.h"

NS_CC_BEGIN

CCActionWatcher::CCActionWatcher() :
m_doneFunc(NULL),
m_mustAllDone(true),
m_valid(true) {
	
}

CCActionWatcher::~CCActionWatcher() {
    CC_SAFE_RELEASE(m_doneFunc);
}

CCActionWatcher* CCActionWatcher::create(CCCallFunc* doneFunc) {
	CCActionWatcher* l = new CCActionWatcher();
	if(l->init(doneFunc)) {
		return (CCActionWatcher*)l->autorelease();
	}
	CC_SAFE_RELEASE(l);
	return NULL;
}

bool CCActionWatcher::init(CCCallFunc* doneFunc) {
    m_doneFunc = doneFunc;
    CC_SAFE_RETAIN(m_doneFunc);
	return true;
}

void CCActionWatcher::onActionRemoved(CCAction* a) {
    if(a->isDone()) {
        m_waitList.removeObject(a);
    } else {
        if(m_mustAllDone) {
            m_valid = false;
            m_waitList.removeAllObjects();
        } else {
            m_waitList.removeObject(a);
        }
    }
    
    // if all clear, perform done function
    if(m_valid && m_waitList.count() <= 0 && m_doneFunc) {
        m_doneFunc->execute();
        m_valid = false;
    }
}

void CCActionWatcher::waitAction(CCAction* a) {
    m_waitList.addObject(a);
}

NS_CC_END