//
//  CCActionWatcher.h
//  cocos2dx
//
//  Created on 14/12/31.
//  Copyright (c) 2014年 cocos2d-x. All rights reserved.
//

#ifndef __cocos2dx__CCActionWatcher__
#define __cocos2dx__CCActionWatcher__

#include "ccTypes.h"
#include "cocoa/CCArray.h"
#include "actions/CCAction.h"
#include "actions/CCActionInstant.h"

NS_CC_BEGIN

/**
 * a watcher which waits for some actions completed, then do something
 */
class CCActionWatcher : public CCObject {
private:
    CCArray m_waitList;
    
public:
    CCActionWatcher();
	virtual ~CCActionWatcher();
	static CCActionWatcher* create(CCCallFunc* doneFunc);
	
	virtual bool init(CCCallFunc* doneFunc);
    
    void onActionRemoved(CCAction* a);
    void waitAction(CCAction* a);
    
    /// the function to be called when waiting list is clear
    CC_SYNTHESIZE_RETAIN(CCCallFunc*, m_doneFunc, DoneFunc);
    
    /// if true, all actions in waiting list must be done, otherwise the done function will not
    /// be invoked, by default, it is true
    CC_SYNTHESIZE_BOOL(m_mustAllDone, MustAllDone);
    
    /// if true, this watcher is still valid
    CC_SYNTHESIZE_BOOL(m_valid, Valid);
};

NS_CC_END

#endif /* defined(__cocos2dx__CCActionWatcher__) */
