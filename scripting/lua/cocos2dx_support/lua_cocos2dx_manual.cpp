/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
#include "lua_cocos2dx_manual.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

static int lua_cocos2dx_manual_CCNode_setScriptUserData(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = nullptr;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_manual_CCNode_setScriptUserData'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_manual_CCNode_setScriptUserData'", nullptr);
        return 0;
    }
#endif
    
    // get argument count
    argc = lua_gettop(tolua_S) - 1;
    
    // if argument count matched, call
    if (argc == 1) {
        int refId = 0;
        
        // convert lua value to desired arguments
        if(lua_istable(tolua_S, 2)) {
            refId = toluafix_ref_table(tolua_S, 2, 0);
            if(refId == 0) {
                ok = false;
            }
        } else {
            ok = false;
        }
        
        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_manual_CCNode_setScriptUserData'", nullptr);
            return 0;
        }
        
        // call function
        cobj->_setScriptUserData(refId);
        return 0;
    }
    
    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setScriptUserData", argc, 1);
    return 0;
}

int lua_cocos2dx_manual_CCNode_getScriptUserData(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_manual_CCNode_getScriptUserData'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_manual_CCNode_getScriptUserData'", nullptr);
        return 0;
    }
#endif
    
    // get argument count
    argc = lua_gettop(tolua_S) - 1;
    
    // if argument count matched, call
    if (argc == 0) {
        // call function
        int refId = cobj->_getScriptUserData();
        toluafix_get_table_by_refid(tolua_S, refId);
        return 1;
    }
    
    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getScriptUserData", argc, 0);
    return 0;
}

static int lua_register_cocos2dx_manual_CCNode(lua_State* tolua_S) {
    tolua_beginmodule(tolua_S, "CCNode");
        tolua_function(tolua_S, "setScriptUserData", lua_cocos2dx_manual_CCNode_setScriptUserData);
        tolua_function(tolua_S, "getScriptUserData", lua_cocos2dx_manual_CCNode_getScriptUserData);
    tolua_endmodule(tolua_S);
    return 1;
}

int register_all_cocos2dx_manual(lua_State* tolua_S) {
    tolua_open(tolua_S);
    tolua_beginmodule(tolua_S, nullptr);
        lua_register_cocos2dx_manual_CCNode(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}