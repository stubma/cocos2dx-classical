-- usage: (use instead of ant)

_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}

-- register CCObject types
local CCObjectTypes = require("cocos2dx_classes")
for i = 1, #CCObjectTypes do
    _push_functions[CCObjectTypes[i]] = "toluafix_pushusertype_ccobject"
end

-- register CCObject types
CCObjectTypes = require("cocos-ext_classes")
for i = 1, #CCObjectTypes do
    _push_functions[CCObjectTypes[i]] = "toluafix_pushusertype_ccobject"
end

-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
_to_functions["LUA_FUNCTION"] = "toluafix_ref_function"
_is_functions["LUA_FUNCTION"] = "toluafix_isfunction"
_to_functions["LUA_TABLE"] = "toluafix_totable"
_is_functions["LUA_TABLE"] = "toluafix_istable"

local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

function output(s)
    out = _OUTPUT
    output = OUTPUT -- restore
    output(s)
end

function write(a)
    if out == _OUTPUT then
        currentString = currentString .. a
        if string.sub(currentString,-1) == '\n'  then
            toWrite[#toWrite+1] = currentString
            currentString = ''
        end
    else
        WRITE(a)
    end
end

function get_property_methods_hook(ptype, name)
    name = name:gsub("^m_(.-)", "%1")
    name = name:gsub("^%l", string.upper)  
    if ptype == "default" then
        return "get" .. name, "set" .. name  
    elseif ptype == "bool" then  
        return "is" .. name, "set" .. name  
    end  
end  

function post_output_hook(package)
    local result = table.concat(toWrite)
    local function replace(pattern, replacement)
        local k = 0
        local nxt, currentString = 1, ''
        repeat
            local s, e = string.find(result, pattern, nxt, true)
            if e then
                currentString = currentString .. string.sub(result, nxt, s-1) .. replacement
                nxt = e + 1
                k = k + 1
            end
        until not e
        result = currentString..string.sub(result, nxt)
        if k == 0 then print('Pattern not replaced', pattern) end
    end

    replace([[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]],
      [[/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

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

extern "C" {
#include "tolua_fix.h"
}

#include <string>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "lua_cocos2d_auto.h"
#include "support/ui_support/CCScrollBar.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;]])

    replace([[/* Exported function */
TOLUA_API int  tolua_cocos2d_open (lua_State* tolua_S);]], [[]])

    replace([[*((LUA_FUNCTION*)]], [[(]])

    replace([[tolua_usertype(tolua_S,"LUA_FUNCTION");]], [[]])

    replace([[toluafix_pushusertype_ccobject(tolua_S,(void*)tolua_ret]],
        [[int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret]])

    replace([[int tolua_ret = (int)  self->getFileData(pszFileName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);]],
        [[unsigned long size = 0;
    unsigned char* buffer = self->getFileData(pszFileName, "rb", &size);
    if (buffer && size)
    {
        lua_pushlstring(tolua_S, (char*)buffer, size);
    }
    else
    {
        lua_pushnil(tolua_S);
    }
    if (buffer) delete[] buffer;]])

    replace([[int tolua_ret = (int)  self->getFileDataFromZip(pszZipFilePath,pszFileName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);]],
        [[unsigned long size = 0;
    unsigned char* buffer = self->getFileDataFromZip(pszZipFilePath, pszFileName, &size);
    if (buffer && size)
    {
        lua_pushlstring(tolua_S, (char*)buffer, size);
    }
    else
    {
        lua_pushnil(tolua_S);
    }
    if (buffer) delete[] buffer;]])

    result = string.gsub(result,
        [[tolua_usertype%(tolua_S,"([%a%d]+)"%);]],
        [[tolua_usertype(tolua_S,"%1");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(%1)), "%1");]])

    result = string.gsub(result, 
        [[toluafix_pushusertype_ccobject%(tolua_S,%(void%*%)&(.-),(.-)%);]],
        [[int nID = (int)%1.m_uID;
    int* pLuaID = &%1.m_nLuaID;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)&%1,%2);]])

    result = string.gsub(result, 
        [[toluafix_pushusertype_ccobject%(tolua_S,%(void%*%)(.-),(.-)%);]],
        [[int nID = (%1) ? (int)%1->m_uID : -1;
    int* pLuaID = (%1) ? &(%1)->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)%1,%2);]])

    WRITE(result)
end
