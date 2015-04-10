/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Erawppa
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCNotificationCenter.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"
#include "cocoa/CCString.h"
#include "script_support/CCScriptSupport.h"
#include <string>

using namespace std;

NS_CC_BEGIN

static CCNotificationCenter *s_sharedNotifCenter = NULL;

CCNotificationCenter::CCNotificationCenter()
{
    m_observers = CCArray::createWithCapacity(3);
    CC_SAFE_RETAIN(m_observers);
}

CCNotificationCenter::~CCNotificationCenter()
{
    CC_SAFE_RELEASE(m_observers);
}

CCNotificationCenter *CCNotificationCenter::sharedNotificationCenter(void)
{
    if (!s_sharedNotifCenter)
    {
        s_sharedNotifCenter = new CCNotificationCenter;
    }
    return s_sharedNotifCenter;
}

void CCNotificationCenter::purgeNotificationCenter(void)
{
    CC_SAFE_RELEASE_NULL(s_sharedNotifCenter);
}

//
// internal functions
//
bool CCNotificationCenter::observerExisted(CCObject *target,const char *name)
{
    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_observers, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (!observer)
            continue;
        
        if (!strcmp(observer->getName(),name) && observer->getTarget() == target)
            return true;
    }
    return false;
}

//
// observer functions
//
void CCNotificationCenter::addObserver(CCObject *target, 
                                       SEL_CallFuncO selector,
                                       const char *name,
                                       CCObject *obj)
{
    if (this->observerExisted(target, name))
        return;
    
    CCNotificationObserver *observer = new CCNotificationObserver(target, selector, name, obj);
    if (!observer)
        return;
    
    CC_SAFE_AUTORELEASE(observer);
    m_observers->addObject(observer);
}

void CCNotificationCenter::removeObserver(CCObject *target,const char *name)
{
    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_observers, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (!observer)
            continue;
        
        if (!strcmp(observer->getName(),name) && observer->getTarget() == target)
        {
            m_observers->removeObject(observer);
            return;
        }
    }
}

int CCNotificationCenter::removeAllObservers(CCObject *target)
{
    CCObject *obj = NULL;
    CCArray *toRemove = CCArray::create();

    CCARRAY_FOREACH(m_observers, obj)
    {
        CCNotificationObserver *observer = (CCNotificationObserver *)obj;
        if (!observer)
            continue;

        if (observer->getTarget() == target)
        {
            toRemove->addObject(observer);
        }
    }

    m_observers->removeObjectsInArray(toRemove);
    return toRemove->count();
}

void CCNotificationCenter::registerScriptObserver(ccScriptFunction func, const char* name)
{
    
    if (this->observerExisted(func.target, name))
        return;
    
    CCNotificationObserver *observer = new CCNotificationObserver(func, name, NULL);
    if (!observer)
        return;
    
    CC_SAFE_AUTORELEASE(observer);
    m_observers->addObject(observer);
}

void CCNotificationCenter::unregisterScriptObserver(CCObject *target,const char* name)
{        
    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_observers, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (!observer)
            continue;
            
        if ( !strcmp(observer->getName(),name) && observer->getHandler().target == target)
        {
            m_observers->removeObject(observer);
        }
    }
}

void CCNotificationCenter::postNotificationWithArray(const char *name, CCArray* array) {
    postNotification(name, array);
}

void CCNotificationCenter::postNotificationWithDict(const char *name, CCDictionary* dict) {
    postNotification(name, dict);
}

void CCNotificationCenter::postNotification(const char *name, CCObject *object)
{
    CCArray* ObserversCopy = CCArray::createWithCapacity(m_observers->count());
    ObserversCopy->addObjectsFromArray(m_observers);
    CCObject* obj = NULL;
    CCARRAY_FOREACH(ObserversCopy, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (!observer)
            continue;
        
        if (!strcmp(name,observer->getName()) && (observer->getObject() == object || observer->getObject() == NULL || object == NULL))
        {
            if (0 != observer->getHandler().handler)
            {
                CCScriptEngineProtocol* engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
                CCArray args;
                args.addObject(CCString::create(name));
                if(object) {
                    args.addObject(object);
                }
                engine->executeEventWithArgs(observer->getHandler(), &args);
            }
            else
            {
                observer->performSelector(object);
            }
        }
    }
}

void CCNotificationCenter::postNotification(const char *name)
{
    this->postNotification(name,NULL);
}

ccScriptFunction CCNotificationCenter::getObserverHandlerByName(const char* name)
{
    ccScriptFunction dummy = { NULL, 0 };
    if (NULL == name || strlen(name) == 0)
    {
        return dummy;
    }
    
    CCObject* obj = NULL;
    CCARRAY_FOREACH(m_observers, obj)
    {
        CCNotificationObserver* observer = (CCNotificationObserver*) obj;
        if (NULL == observer)
            continue;
        
        if ( 0 == strcmp(observer->getName(),name) )
        {
            return observer->getHandler();
        }
    }
    
    return dummy;
}

////////////////////////////////////////////////////////////////////////////////
///
/// CCNotificationObserver
///
////////////////////////////////////////////////////////////////////////////////
CCNotificationObserver::CCNotificationObserver(CCObject *target, 
                                               SEL_CallFuncO selector,
                                               const char *name,
                                               CCObject *obj)
{
    m_target = target;
    m_selector = selector;
    m_object = obj;
    
    m_name = new char[strlen(name)+1];
    memset(m_name,0,strlen(name)+1);
    
    string orig (name);
    orig.copy(m_name,strlen(name),0);
    memset(&m_func, 0, sizeof(ccScriptFunction));
}

CCNotificationObserver::CCNotificationObserver(ccScriptFunction func, const char* name, CCObject* obj) {
    m_target = NULL;
    m_selector = NULL;
    m_object = obj;
    m_func = func;
    m_name = new char[strlen(name)+1];
    memset(m_name,0,strlen(name)+1);
    string orig (name);
    orig.copy(m_name,strlen(name),0);
}

CCNotificationObserver::~CCNotificationObserver()
{
    CC_SAFE_DELETE_ARRAY(m_name);
    if(m_func.handler) {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_func.handler);
    }
}

void CCNotificationObserver::performSelector(CCObject *obj)
{
    if (m_target)
    {
		if (obj) {
			(m_target->*m_selector)(obj);
		} else {
			(m_target->*m_selector)(m_object);
		}
    }
}

CCObject *CCNotificationObserver::getTarget()
{
    return m_target;
}

SEL_CallFuncO CCNotificationObserver::getSelector()
{
    return m_selector;
}

char *CCNotificationObserver::getName()
{
    return m_name;
}

CCObject *CCNotificationObserver::getObject()
{
    return m_object;
}

NS_CC_END
