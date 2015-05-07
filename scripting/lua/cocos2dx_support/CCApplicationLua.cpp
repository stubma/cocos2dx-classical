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
#include "CCApplicationLua.h"

NS_CC_BEGIN

CCApplicationLua::CCApplicationLua(const std::string& entryScriptFilePath, cc_app_register_func rf) :
m_entryScriptFilePath(entryScriptFilePath),
m_appRegFunc(rf) {
}

CCApplicationLua::~CCApplicationLua() {
    
}

bool CCApplicationLua::applicationDidFinishLaunching() {
    // lua entry, we use compiled lua in release version
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    if(m_appRegFunc) {
        (*m_appRegFunc)(pEngine->getLuaStack()->getLuaState());
    }
    pEngine->executeScriptFile(m_entryScriptFilePath.c_str());
    
    return true;
}

void CCApplicationLua::applicationDidEnterBackground() {
    // redirect event to lua side, you need define global function in lua side
    CCLuaEngine::defaultEngine()->executeString("applicationDidEnterBackground()");
}

void CCApplicationLua::applicationWillEnterForeground() {
    // redirect event to lua side, you need define global function in lua side
    CCLuaEngine::defaultEngine()->executeString("applicationWillEnterForeground()");
}

NS_CC_END