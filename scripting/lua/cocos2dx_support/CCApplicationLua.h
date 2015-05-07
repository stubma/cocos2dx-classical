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
#ifndef __CCApplicationLua__
#define __CCApplicationLua__

#include "platform/CCCommon.h"
#include "platform/CCApplication.h"
#include "CCLuaEngine.h"

NS_CC_BEGIN

/// function to register app lua binding
typedef int (*cc_app_register_func)(lua_State*);

/**
 * A lua application instance which redirects app lifecycle event to
 * lua side. To initialize it, provide an entry script file and a register
 * function(optional)
 */
class CC_DLL CCApplicationLua : public CCApplication {
public:
    CCApplicationLua(const std::string& entryScriptFilePath, cc_app_register_func rf = NULL);
    virtual ~CCApplicationLua();
    
    /**
     @brief    Implement CCDirector and CCScene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching();
    
    /**
     @brief  The function be called when the application enter background
     @param  the pointer of the application
     */
    virtual void applicationDidEnterBackground();
    
    /**
     @brief  The function be called when the application enter foreground
     @param  the pointer of the application
     */
    virtual void applicationWillEnterForeground();
    
    CC_SYNTHESIZE_PASS_BY_REF(std::string, m_entryScriptFilePath, EntryScriptFilePath);
    CC_SYNTHESIZE(cc_app_register_func, m_appRegFunc, AppRegisterFunction);
};

NS_CC_END

#endif /* defined(__CCApplicationLua__) */
