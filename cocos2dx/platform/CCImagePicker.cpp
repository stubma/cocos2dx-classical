/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-classical
 
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
#include "CCImagePicker.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCString.h"

NS_CC_BEGIN

CCImagePicker::CCImagePicker() :
m_callback(NULL),
m_expectedWidth(100),
m_expectedHeight(100),
m_keepRatio(true),
m_useFrontCamera(false),
m_path("output.jpg") {
    memset(&m_scriptHandler, 0, sizeof(ccScriptFunction));
}

CCImagePicker::~CCImagePicker() {
    unregisterScriptHandler();
}

CCImagePicker* CCImagePicker::create() {
    CCImagePicker* p = new CCImagePicker();
    return (CCImagePicker*)p->autorelease();
}

void CCImagePicker::setScriptHandler(ccScriptFunction handler) {
    unregisterScriptHandler();
    m_scriptHandler = handler;
}

void CCImagePicker::unregisterScriptHandler() {
    if(m_scriptHandler.handler) {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_scriptHandler.handler);
        m_scriptHandler.handler = 0;
    }
}

void CCImagePicker::notifyImagePickedOK() {
    if(m_callback) {
        m_callback->onImagePicked(this);
    }
    if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(2);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("pick_ok"));
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    }
}

void CCImagePicker::notifyImagePickingCancelled() {
    if(m_callback) {
        m_callback->onImagePickingCancelled(this);
    }
    if(m_scriptHandler.handler) {
        CCArray* pArrayArgs = CCArray::createWithCapacity(2);
        pArrayArgs->addObject(this);
        pArrayArgs->addObject(CCString::create("pick_cancelled"));
        CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEventWithArgs(m_scriptHandler, pArrayArgs);
    }
}

NS_CC_END