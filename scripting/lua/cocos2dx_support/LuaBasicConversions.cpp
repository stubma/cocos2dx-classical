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

#include "LuaBasicConversions.h"
#include "tolua_fix.h"



std::map<std::string, std::string>  g_luaType;
std::map<std::string, std::string>  g_typeCast;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName)
{
    if (nullptr == L || nullptr == err || nullptr == msg || 0 == strlen(msg))
        return;

    if (msg[0] == '#')
    {
        const char* expected = err->type;
        const char* provided = tolua_typename(L,err->index);
        if (msg[1]=='f')
        {
            int narg = err->index;
            if (err->array)
                CCLOG("%s\n     %s argument #%d is array of '%s'; array of '%s' expected.\n",msg+2,funcName,narg,provided,expected);
            else
                CCLOG("%s\n     %s argument #%d is '%s'; '%s' expected.\n",msg+2,funcName,narg,provided,expected);
        }
        else if (msg[1]=='v')
        {
            if (err->array)
                CCLOG("%s\n     %s value is array of '%s'; array of '%s' expected.\n",funcName,msg+2,provided,expected);
            else
                CCLOG("%s\n     %s value is '%s'; '%s' expected.\n",msg+2,funcName,provided,expected);
        }
    }
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int lua_isusertype (lua_State* L, int lo, const char* type);
#ifdef __cplusplus
}
#endif

bool luaval_is_usertype(lua_State* L,int lo,const char* type, int def)
{
    if (def && lua_gettop(L)<abs(lo))
        return true;
    
    if (lua_isnil(L,lo) || lua_isusertype(L,lo,type))
        return true;
    
    return false;
}

bool luaval_to_ushort(lua_State* L, int lo, unsigned short* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (unsigned short)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}


bool luaval_to_int32(lua_State* L,int lo,int* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (int)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_luafunc(lua_State* L, int lo, cocos2d::ccScriptFunction* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    tolua_Error tolua_err;
    if(!toluafix_isfunction(L, lo, "LUA_FUNCTION", 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        outValue->handler = (unsigned int)toluafix_ref_function(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (unsigned int)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (unsigned char)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_boolean(lua_State* L,int lo,bool* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isboolean(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (bool)tolua_toboolean(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_number(lua_State* L,int lo,double* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_long_long(lua_State* L,int lo,long long* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (long long)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_iscppstring(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = tolua_tocppstring(L,lo,nullptr);
    }
    
    return ok;
}

bool luaval_to_position(lua_State* L, int lo, cocos2d::ccPosition* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:", &tolua_err, funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0 : (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0 : (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_aabb(lua_State* L, int lo, cocos2d::ccAABB* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "min");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_point(L, -1, &outValue->min);
        lua_pop(L, 1);
        
        lua_pushstring(L, "max");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_point(L, -1, &outValue->max);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_quad3(lua_State* L, int lo, cocos2d::ccQuad3* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "bl");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_vertex3f(L, -1, &outValue->bl);
        lua_pop(L, 1);
        
        lua_pushstring(L, "br");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_vertex3f(L, -1, &outValue->br);
        lua_pop(L, 1);
        
        lua_pushstring(L, "tl");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_vertex3f(L, -1, &outValue->tl);
        lua_pop(L, 1);
        
        lua_pushstring(L, "tr");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_vertex3f(L, -1, &outValue->tr);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_vertex2f(lua_State* L, int lo, cocos2d::ccVertex2F* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_vertex3f(lua_State* L, int lo, cocos2d::ccVertex3F* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "z");
        lua_gettable(L, lo);
        outValue->z = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_packetheader(lua_State* L, int lo, cocos2d::ccPacketHeader* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "magic");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1)) {
            int magic;
            luaval_to_int32(L, -1, &magic);
            magic = htobe32(magic);
            memcpy(outValue->magic, &magic, 4);
        }
        lua_pop(L, 1);
        
        lua_pushstring(L, "protocolVersion");
        lua_gettable(L, lo);
        outValue->protocolVersion = lua_isnil(L, -1) ? 0 : (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "serverVersion");
        lua_gettable(L, lo);
        outValue->serverVersion = lua_isnil(L, -1) ? 0 : (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "command");
        lua_gettable(L, lo);
        outValue->command = lua_isnil(L, -1) ? 0 : (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "encryptAlgorithm");
        lua_gettable(L, lo);
        outValue->encryptAlgorithm = lua_isnil(L, -1) ? 0 : (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "length");
        lua_gettable(L, lo);
        outValue->length = lua_isnil(L, -1) ? 0 : (int)lua_tointeger(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_bezierconfig(lua_State* L, int lo, cocos2d::ccBezierConfig* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "endPosition");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_point(L, -1, &outValue->endPosition, funcName);
        lua_pop(L, 1);
        
        lua_pushstring(L, "controlPoint_1");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_point(L, -1, &outValue->controlPoint_1, funcName);
        lua_pop(L, 1);
        
        lua_pushstring(L, "controlPoint_2");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1))
            luaval_to_point(L, -1, &outValue->controlPoint_2, funcName);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_csize(lua_State* L,int lo, cocos2d::ccSize* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be a table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L, "#ferror:", &tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "width");
        lua_gettable(L, lo);
        outValue->width = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "height");
        lua_gettable(L, lo);
        outValue->height = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_cpoint(lua_State* L, int lo, cocos2d::ccPoint* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be a table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L, "#ferror:", &tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_v2fc4bt2fquad(lua_State* L, int lo, cocos2d::ccV2F_C4B_T2F_Quad* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be a table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "bl");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_v2fc4bt2f(L, -1, &outValue->bl);
        lua_pop(L, 1);
        
        lua_pushstring(L, "br");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_v2fc4bt2f(L, -1, &outValue->br);
        lua_pop(L, 1);
        
        lua_pushstring(L, "tl");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_v2fc4bt2f(L, -1, &outValue->tl);
        lua_pop(L, 1);
        
        lua_pushstring(L, "tr");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_v2fc4bt2f(L, -1, &outValue->tr);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_v3fc4bt2fquad(lua_State* L, int lo, cocos2d::ccV3F_C4B_T2F_Quad* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be a table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "bl");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_v3fc4bt2f(L, -1, &outValue->bl);
        lua_pop(L, 1);
        
        lua_pushstring(L, "br");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_v3fc4bt2f(L, -1, &outValue->br);
        lua_pop(L, 1);
        
        lua_pushstring(L, "tl");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_v3fc4bt2f(L, -1, &outValue->tl);
        lua_pop(L, 1);
        
        lua_pushstring(L, "tr");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_v3fc4bt2f(L, -1, &outValue->tr);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_v2fc4bt2f(lua_State* L, int lo, cocos2d::ccV2F_C4B_T2F* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be a table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "vertices");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_vertex2f(L, -1, &outValue->vertices);
        lua_pop(L, 1);
        
        lua_pushstring(L, "colors");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_color4b(L, -1, &outValue->colors);
        lua_pop(L, 1);
        
        lua_pushstring(L, "texCoords");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_tex2f(L, -1, &outValue->texCoords);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_v3fc4bt2f(lua_State* L, int lo, cocos2d::ccV3F_C4B_T2F* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be a table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "vertices");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_vertex3f(L, -1, &outValue->vertices);
        lua_pop(L, 1);
        
        lua_pushstring(L, "colors");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_color4b(L, -1, &outValue->colors);
        lua_pop(L, 1);
        
        lua_pushstring(L, "texCoords");
        lua_gettable(L, lo);
        if(lua_isnil(L, -1))
            luaval_to_tex2f(L, -1, &outValue->texCoords);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_tex2f(lua_State* L, int lo, cocos2d::ccTex2F* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be a table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "u");
        lua_gettable(L, lo);
        outValue->u = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "v");
        lua_gettable(L, lo);
        outValue->v = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_mat4(lua_State* L, int lo, kmMat4* outValue , const char* funcName) {
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L, "#ferror:", &tolua_err,funcName);
        ok = false;
#endif
    }
    
    if (ok) {
        do {
            size_t len = lua_objlen(L, lo);
            if (len != 16) {
                ok = false;
                break;
            }
            for (size_t i = 0; i < len; i++) {
                lua_pushnumber(L, i + 1);
                lua_gettable(L,lo);
                if (tolua_isnumber(L, -1, 0, &tolua_err)) {
                    outValue->mat[i] = tolua_tonumber(L, -1, 0);
                } else {
                    outValue->mat[i] = 0;
                }
                lua_pop(L, 1);
            }
        } while (0);
    }
    
    return ok;
}

bool luaval_to_customuniformvalue(lua_State* L, int lo, cocos2d::ccCustomUniformValue* outValue , const char* funcName ) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // must be table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L, "#ferror:", &tolua_err,funcName);
#endif
        ok = false;
    }
    
    // must have __union field
    ccShaderType type;
    lua_pushstring(L, "type");
    lua_gettable(L, lo);
    if(lua_isnil(L, -1) || !lua_isnumber(L, -1)) {
        ok = false;
    } else {
        type = (ccShaderType)lua_tointeger(L, -1);
    }
    lua_pop(L, 1);
    
    // conversion based on __union
    if(ok) {
        switch (type) {
            case cocos2d::kCCShader_blur:
                lua_pushstring(L, "nodeSize");
                lua_gettable(L, lo);
                luaval_to_csize(L, -1, &outValue->blur.nodeSize);
                lua_pop(L, 1);
                
                lua_pushstring(L, "blurSize");
                lua_gettable(L, lo);
                luaval_to_csize(L, -1, &outValue->blur.blurSize);
                lua_pop(L, 1);
                
                lua_pushstring(L, "subtract");
                lua_gettable(L, lo);
                luaval_to_color4f(L, -1, &outValue->blur.subtract);
                lua_pop(L, 1);
                break;
            case cocos2d::kCCShader_flash:
                lua_pushstring(L, "r");
                lua_gettable(L, lo);
                outValue->flash.r = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
                lua_pop(L, 1);
                
                lua_pushstring(L, "g");
                lua_gettable(L, lo);
                outValue->flash.g = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
                lua_pop(L, 1);
                
                lua_pushstring(L, "b");
                lua_gettable(L, lo);
                outValue->flash.b = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
                lua_pop(L, 1);
                
                lua_pushstring(L, "t");
                lua_gettable(L, lo);
                outValue->flash.t = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
                lua_pop(L, 1);
                break;
            case cocos2d::kCCShader_lighting:
                lua_pushstring(L, "mul");
                lua_gettable(L, lo);
                luaval_to_color4b(L, -1, &outValue->lighting.mul);
                lua_pop(L, 1);
                
                lua_pushstring(L, "add");
                lua_gettable(L, lo);
                luaval_to_color3b(L, -1, &outValue->lighting.add);
                lua_pop(L, 1);
                break;
            case cocos2d::kCCShader_matrix:
                lua_pushstring(L, "mat4");
                lua_gettable(L, lo);
                luaval_to_mat4(L, -1, &outValue->matrix.mat4);
                lua_pop(L, 1);
                break;
            case cocos2d::kCCShader_shine:
                lua_pushstring(L, "width");
                lua_gettable(L, lo);
                outValue->shine.width = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
                lua_pop(L, 1);
                
                lua_pushstring(L, "time");
                lua_gettable(L, lo);
                outValue->shine.time = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
                lua_pop(L, 1);
                
                lua_pushstring(L, "lb");
                lua_gettable(L, lo);
                luaval_to_cpoint(L, -1, &outValue->shine.lb);
                lua_pop(L, 1);
                
                lua_pushstring(L, "rt");
                lua_gettable(L, lo);
                luaval_to_cpoint(L, -1, &outValue->shine.rt);
                lua_pop(L, 1);
                
                lua_pushstring(L, "color1");
                lua_gettable(L, lo);
                luaval_to_color4b(L, -1, &outValue->shine.color1);
                lua_pop(L, 1);
                
                lua_pushstring(L, "color2");
                lua_gettable(L, lo);
                luaval_to_color4b(L, -1, &outValue->shine.color2);
                lua_pop(L, 1);
                
                lua_pushstring(L, "color3");
                lua_gettable(L, lo);
                luaval_to_color4b(L, -1, &outValue->shine.color3);
                lua_pop(L, 1);
                
                lua_pushstring(L, "gradientPositions");
                lua_gettable(L, lo);
                luaval_to_vertex3f(L, -1, &outValue->shine.gradientPositions);
                lua_pop(L, 1);
                break;
            default:
                break;
        }
    }
    return ok;
}

bool luaval_to_point(lua_State* L,int lo,cocos2d::CCPoint* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    
    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L, lo);
        outValue->x = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "y");
        lua_gettable(L, lo);
        outValue->y = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_blendfunc(lua_State* L, int lo, cocos2d::ccBlendFunc* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    
    if (ok)
    {
        lua_pushstring(L, "src");
        lua_gettable(L, lo);
        outValue->src = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "dst");
        lua_gettable(L, lo);
        outValue->dst = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    return ok;
}

bool luaval_to_ssize(lua_State* L,int lo, ssize_t* outValue, const char* funcName)
{
    return luaval_to_long(L, lo, reinterpret_cast<long*>(outValue));
}

bool luaval_to_long(lua_State* L,int lo, long* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (long)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_ulong(lua_State* L,int lo, unsigned long* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_isnumber(L,lo,0,&tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        *outValue = (unsigned long)tolua_tonumber(L, lo, 0);
    }
    
    return ok;
}

bool luaval_to_size(lua_State* L,int lo, CCSize* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "width");  /* L: paramStack key */
        lua_gettable(L,lo);/* L: paramStack paramStack[lo][key] */
        outValue->width = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);/* L: paramStack*/
        
        lua_pushstring(L, "height");
        lua_gettable(L,lo);
        outValue->height = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_crect(lua_State* L, int lo, cocos2d::ccRect* outValue, const char* funcName) {
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L,lo);
        outValue->x = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "y");
        lua_gettable(L,lo);
        outValue->y = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "width");
        lua_gettable(L,lo);
        outValue->width = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "height");
        lua_gettable(L,lo);
        outValue->height = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_rect(lua_State* L,int lo, CCRect* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "x");
        lua_gettable(L,lo);
        outValue->origin.x = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "y");
        lua_gettable(L,lo);
        outValue->origin.y = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "width");
        lua_gettable(L,lo);
        outValue->size.width = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "height");
        lua_gettable(L,lo);
        outValue->size.height = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_color4b(lua_State* L,int lo,ccColor4B* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if(ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "a");
        lua_gettable(L,lo);
        outValue->a = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_colorhsv(lua_State* L,int lo, ccColorHSV* outValue, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == outValue)
        return false;
    bool ok = true;
    
    // top should be a table
    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err))  {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        lua_pushstring(L, "h");
        lua_gettable(L, lo);
        outValue->h = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "s");
        lua_gettable(L, lo);
        outValue->s = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
        
        lua_pushstring(L, "v");
        lua_gettable(L, lo);
        outValue->v = lua_isnil(L, -1) ? 0 : lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    
    return ok;
}

bool luaval_to_color4f(lua_State* L,int lo,ccColor4F* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "a");
        lua_gettable(L,lo);
        outValue->a = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_color3b(lua_State* L,int lo,ccColor3B* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        lua_pushstring(L, "r");
        lua_gettable(L,lo);
        outValue->r = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "g");
        lua_gettable(L,lo);
        outValue->g = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "b");
        lua_gettable(L,lo);
        outValue->b = lua_isnil(L,-1) ? 0 : lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    
    return ok;
}

bool luaval_to_affinetransform(lua_State* L,int lo, CCAffineTransform* outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        do
        {
            lua_pushstring(L, "a");
            lua_gettable(L,lo);
            if (lua_isnil(L,-1))
            {
                ok = false;
                lua_pop(L, 1);
                break;
            }
            outValue->a = (float)lua_tonumber(L,-1);
            
            lua_pushstring(L, "b");
            lua_gettable(L,lo);
            if (lua_isnil(L,-1))
            {
                ok = false;
                lua_pop(L, 1);
                break;
            }
            outValue->b = (float)lua_tonumber(L,-1);
            lua_pop(L,1);
            
            lua_pushstring(L, "c");
            lua_gettable(L,lo);
            if (lua_isnil(L,-1))
            {
                ok = false;
                lua_pop(L, 1);
                break;
            }
            outValue->c =(float)lua_tonumber(L,-1);
            lua_pop(L,1);
            
            lua_pushstring(L, "d");
            lua_gettable(L,lo);
            if (lua_isnil(L,-1))
            {
                ok = false;
                lua_pop(L, 1);
                break;
            }
            outValue->d = (float)lua_tonumber(L,-1);
            lua_pop(L,1);
            
            lua_pushstring(L, "tx");
            lua_gettable(L,lo);
            if (lua_isnil(L,-1))
            {
                ok = false;
                lua_pop(L, 1);
                break;
            }
            outValue->tx = lua_isnil(L,-1) ? 0 : (float)lua_tonumber(L,-1);
            lua_pop(L,1);
            
            lua_pushstring(L, "ty");
            lua_gettable(L,lo);
            if (lua_isnil(L,-1))
            {
                ok = false;
                lua_pop(L, 1);
                break;
            }
            outValue->ty = lua_isnil(L,-1) ? 0 : (float)lua_tonumber(L,-1);
            lua_pop(L,1);
        }
        while (0);
    }
    return ok;
}

bool luaval_to_fontdefinition(lua_State* L, int lo, ccFontDefinition* outValue , const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
        ok = false;
#endif
    }
    
    if (ok)
    {
        // defaul values
        const char *            defautlFontName         = "Arial";
        const int               defaultFontSize         = 32;
        CCTextAlignment         defaultTextAlignment    = kCCTextAlignmentLeft;
        CCVerticalTextAlignment defaultTextVAlignment   = kCCVerticalTextAlignmentTop;
        
        // by default shadow and stroke are off
        outValue->m_shadow.m_shadowEnabled = false;
        outValue->m_stroke.m_strokeEnabled = false;
        
        // white text by default
        outValue->m_fontFillColor = ccWHITE;
        
        lua_pushstring(L, "fontName");
        lua_gettable(L,lo);
        outValue->m_fontName = tolua_tocppstring(L,lo,defautlFontName);
        lua_pop(L,1);
        
        lua_pushstring(L, "fontSize");
        lua_gettable(L,lo);
        outValue->m_fontSize = lua_isnil(L,-1) ? defaultFontSize : (int)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "fontAlignmentH");
        lua_gettable(L,lo);
        outValue->m_alignment = lua_isnil(L,-1) ? defaultTextAlignment : (CCTextAlignment)(int)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "fontAlignmentV");
        lua_gettable(L,lo);
        outValue->m_vertAlignment = lua_isnil(L,-1) ? defaultTextVAlignment : (CCVerticalTextAlignment)(int)lua_tonumber(L,-1);
        lua_pop(L,1);
        
        lua_pushstring(L, "fontFillColor");
        lua_gettable(L,lo);
        if (!lua_isnil(L,-1))
        {
            luaval_to_color3b(L, -1, &outValue->m_fontFillColor);
        }
        lua_pop(L,1);
        
        lua_pushstring(L, "fontDimensions");
        lua_gettable(L,lo);
        if (!lua_isnil(L,-1))
        {
            luaval_to_size(L, -1, &outValue->m_dimensions);
        }
        lua_pop(L,1);
        
        lua_pushstring(L, "shadowEnabled");
        lua_gettable(L,lo);
        if (!lua_isnil(L,-1))
        {
            luaval_to_boolean(L, -1, &outValue->m_shadow.m_shadowEnabled);
            if (outValue->m_shadow.m_shadowEnabled)
            {
                // default shadow values
                outValue->m_shadow.m_shadowOffset  = CCSizeMake(5, 5);
                outValue->m_shadow.m_shadowBlur    = 1;
                outValue->m_shadow.m_shadowOpacity = 1;
            }
            
            lua_pushstring(L, "shadowOffset");
            lua_gettable(L,lo);
            if (!lua_isnil(L,-1))
            {
                luaval_to_size(L, -1, &outValue->m_shadow.m_shadowOffset);
            }
            lua_pop(L,1);
            
            lua_pushstring(L, "shadowBlur");
            lua_gettable(L,lo);
            if (!lua_isnil(L,-1))
            {
               outValue->m_shadow.m_shadowBlur = (float)lua_tonumber(L,-1);
            }
            lua_pop(L,1);
            
            lua_pushstring(L, "shadowOpacity");
            lua_gettable(L,lo);
            if (!lua_isnil(L,-1))
            {
                outValue->m_shadow.m_shadowOpacity = lua_tonumber(L,-1);
            }
            lua_pop(L,1);
        }
        lua_pop(L,1);
        
        lua_pushstring(L, "strokeEnabled");
        lua_gettable(L,lo);
        if (!lua_isnil(L,-1))
        {
            luaval_to_boolean(L, -1, &outValue->m_stroke.m_strokeEnabled);
            if (outValue->m_stroke.m_strokeEnabled)
            {
                // default stroke values
                outValue->m_stroke.m_strokeSize  = 1;
                outValue->m_stroke.m_strokeColor = ccBLUE;
                
                lua_pushstring(L, "strokeColor");
                lua_gettable(L,lo);
                if (!lua_isnil(L,-1))
                {
                     luaval_to_color3b(L, -1, &outValue->m_stroke.m_strokeColor);
                }
                lua_pop(L,1);
                
                lua_pushstring(L, "strokeSize");
                lua_gettable(L,lo);
                if (!lua_isnil(L,-1))
                {
                    outValue->m_stroke.m_strokeSize = (float)lua_tonumber(L,-1);
                }
                lua_pop(L,1);
            }
        }
        lua_pop(L,1);
        
        lua_pushstring(L, "shadowColor");
        lua_gettable(L, lo);
        if (!lua_isnil(L, -1)) {
            luaval_to_int32(L, -1, &outValue->m_shadowColor);
        }
        lua_pop(L, 1);
        
        lua_pushstring(L, "lineSpacing");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1)) {
            double tmp;
            luaval_to_number(L, -1, &tmp);
            outValue->m_lineSpacing = (float)tmp;
        }
        lua_pop(L, 1);
        
        lua_pushstring(L, "globalImageScaleFactor");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1)) {
            double tmp;
            luaval_to_number(L, -1, &tmp);
            outValue->m_globalImageScaleFactor = (float)tmp;
        }
        lua_pop(L, 1);
        
        lua_pushstring(L, "toCharIndex");
        lua_gettable(L, lo);
        if (!lua_isnil(L, -1)) {
            luaval_to_int32(L, -1, &outValue->m_toCharIndex);
        }
        lua_pop(L, 1);
        
        lua_pushstring(L, "decryptFunc");
        lua_gettable(L, lo);
        if (!lua_isnil(L, -1)) {
            outValue->decryptFunc = (CC_DECRYPT_FUNC)tolua_touserdata(L, -1, nullptr);
        }
        lua_pop(L, 1);
        
        lua_pushstring(L, "elapsed");
        lua_gettable(L, lo);
        if(!lua_isnil(L, -1)) {
            double tmp;
            luaval_to_number(L, -1, &tmp);
            outValue->m_elapsed = (float)tmp;
        }
        lua_pop(L, 1);
    }
    
    return ok;
}

bool luaval_to_array(lua_State* L,int lo, CCArray** outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        if (len > 0)
        {
            CCArray* arr =  CCArray::createWithCapacity(len);
            if (nullptr == arr)
                return false;
            
            for (size_t i = 0; i < len; i++)
            {
                lua_pushnumber(L,i + 1);
                lua_gettable(L,lo);
                if (lua_isnil(L,-1))
                {
                    lua_pop(L, 1);
                    continue;
                }
                
                if (lua_isuserdata(L, -1)) {
                    CCObject* obj = static_cast<CCObject*>(tolua_tousertype(L, -1, nullptr) );
                    if (nullptr != obj) {
                        arr->addObject(obj);
                    }
                } else if(lua_istable(L, -1)) {
                    lua_pushnumber(L,1);
                    lua_gettable(L,-2);
                    if (lua_isnil(L, -1) ) {
                        lua_pop(L,1);
                        CCDictionary* dictVal = nullptr;
                        if (luaval_to_dictionary(L,-1,&dictVal))
                        {
                            arr->addObject(dictVal);
                        }
                    } else {
                       lua_pop(L,1);
                       CCArray* arrVal = nullptr;
                       if(luaval_to_array(L, -1, &arrVal))
                       {
                           arr->addObject(arrVal);
                       }
                    }
                } else if(lua_type(L, -1) == LUA_TSTRING) {
                    std::string stringValue = "";
                    if(luaval_to_std_string(L, -1, &stringValue)) {
                        arr->addObject(CCString::create(stringValue));
                    }
                } else if(lua_type(L, -1) == LUA_TBOOLEAN) {
                    bool boolVal = false;
                    if (luaval_to_boolean(L, -1, &boolVal)) {
                        arr->addObject(CCBool::create(boolVal));
                    }
                } else if(lua_type(L, -1) == LUA_TNUMBER) {
                    arr->addObject(CCDouble::create(tolua_tonumber(L, -1, 0)));
                } else {
                    CCAssert(false, "not supported type");
                }
                lua_pop(L, 1);
            }
            
            *outValue = arr;
        }
    }
    
    return ok;
}

bool luaval_to_dictionary(lua_State* L,int lo, CCDictionary** outValue, const char* funcName)
{
    if (nullptr == L || nullptr == outValue)
        return  false;
    
    bool ok = true;

    tolua_Error tolua_err;
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        std::string stringKey = "";
        std::string stringValue = "";
        bool boolVal = false;
        CCDictionary* dict = nullptr;
        lua_pushnil(L);                                             /* L: lotable ..... nil */
        while (0 != lua_next(L, lo )) {
            // if key is not string, ignore
            if (!lua_isstring(L, -2)) {
                lua_pop(L, 1);
                continue;
            }
            
            // lazy create dictionary
            if (nullptr == dict) {
                dict = CCDictionary::create();
            }
            
            if(luaval_to_std_string(L, -2, &stringKey)) {
                if (lua_isuserdata(L, -1)) {
                    CCObject* obj = static_cast<CCObject*>(tolua_tousertype(L, -1, nullptr) );
                    if (nullptr != obj) {
                        //get the key to string
                        dict->setObject(obj, stringKey);
                    }
                } else if(lua_istable(L, -1)) {
                    // if i can't get element by index, we think it is a dictionary
                    // otherwise parse the table as an array
                    lua_pushnumber(L, 1);
                    lua_gettable(L, -2);
                    if (lua_isnil(L, -1)) {
                        lua_pop(L, 1);
                        CCDictionary* dictVal = nullptr;
                        if (luaval_to_dictionary(L, -1, &dictVal)) {
                            dict->setObject(dictVal, stringKey);
                        }
                    } else {
                        lua_pop(L, 1);
                        CCArray* arrVal = nullptr;
                        if(luaval_to_array(L, -1, &arrVal)) {
                            dict->setObject(arrVal,stringKey);
                        }
                    }
                } else if(lua_type(L, -1) == LUA_TSTRING) {
                    if(luaval_to_std_string(L, -1, &stringValue)) {
                        dict->setObject(CCString::create(stringValue), stringKey);
                    }
                }
                else if(lua_type(L, -1) == LUA_TBOOLEAN) {
                    if (luaval_to_boolean(L, -1, &boolVal)) {
                        dict->setObject(CCBool::create(boolVal),stringKey);
                    }
                } else if(lua_type(L, -1) == LUA_TNUMBER) {
                     dict->setObject(CCDouble::create(tolua_tonumber(L, -1, 0)),stringKey);
                } else {
                    CCAssert(false, "not supported type");
                }
            }
            
            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
                                                                    /* L: lotable ..... */
        *outValue = dict;
    }
    
    return ok;
}

bool luaval_to_array_of_point(lua_State* L,int lo,cocos2d::CCPoint **points, int *numPoints, const char* funcName)
{
    if (nullptr == L)
        return false;
    
    bool ok = true;
    
    tolua_Error tolua_err;
    
    if (!tolua_istable(L, lo, 0, &tolua_err) )
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        if (len > 0)
        {
            cocos2d::CCPoint* array = (cocos2d::CCPoint*) new CCPoint[len];
            if (nullptr == array)
                return false;
            for (size_t i = 0; i < len; ++i)
            {
                lua_pushnumber(L,i + 1);
                lua_gettable(L,lo);
                if (!tolua_istable(L,-1, 0, &tolua_err))
                {
#if COCOS2D_DEBUG >=1
                    luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
                    lua_pop(L, 1);
                    CC_SAFE_DELETE_ARRAY(array);
                    return false;
                }
                ok &= luaval_to_point(L, lua_gettop(L), &array[i]);
                if (!ok)
                {
                    lua_pop(L, 1);
                    CC_SAFE_DELETE_ARRAY(array);
                    return false;
                }
                lua_pop(L, 1);
            }
            
            *numPoints = (int)len;
            *points    = array;
        }
    }
    return ok;
}


bool luavals_variadic_to_array(lua_State* L,int argc, CCArray** ret)
{
    if (nullptr == L || argc == 0 )
        return false;
    
    bool ok = true;
    
    CCArray* array = CCArray::create();
    for (int i = 0; i < argc; i++)
    {
        double num = 0.0;
        if (lua_type(L, i + 2) == LUA_TNUMBER )
        {
            ok &= luaval_to_number(L, i + 2, &num);
            if (!ok)
                break;
            
            array->addObject(CCInteger::create((int)num));
        }
        else if (lua_type(L, i + 2) == LUA_TSTRING )
        {
            std::string str = lua_tostring(L, i + 2);
            array->addObject(CCString::create(str));
        }
        else if (lua_isuserdata(L, i + 2))
        {
            tolua_Error err;
            if (!tolua_isusertype(L, i + 2, "CCObject", 0, &err))
            {
#if COCOS2D_DEBUG >=1
                luaval_to_native_err(L,"#ferror:",&err);
#endif
                ok = false;
                break;
            }
            CCObject* obj = static_cast<CCObject*>(tolua_tousertype(L, i + 2, nullptr));
            array->addObject(obj);
        }
    }
    
    *ret = array;
    
    return ok;
}

bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        std::string value = "";
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isstring(L, -1))
            {
                ok = luaval_to_std_string(L, -1, &value);
                if(ok)
                    ret->push_back(value);
            }
            else
            {
                CCAssert(false, "string type is needed");
            }
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isnumber(L, -1))
            {
                ret->push_back((int)tolua_tonumber(L, -1, 0));
            }
            else
            {
                CCAssert(false, "int type is needed");
            }
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

bool luaval_to_std_vector_float(lua_State* L, int lo, std::vector<float>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isnumber(L, -1))
            {
                ret->push_back((float)tolua_tonumber(L, -1, 0));
            }
            else
            {
                CCAssert(false, "float type is needed");
            }
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

bool luaval_to_std_vector_ushort(lua_State* L, int lo, std::vector<unsigned short>* ret, const char* funcName)
{
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok)
    {
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++)
        {
            lua_pushnumber(L, i + 1);
            lua_gettable(L,lo);
            if(lua_isnumber(L, -1))
            {
                ret->push_back((unsigned short)tolua_tonumber(L, -1, 0));
            }
            else
            {
                CCAssert(false, "unsigned short type is needed");
            }
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

bool luaval_to_std_vector_rect(lua_State* L, int lo, std::vector<cocos2d::CCRect>* ret, const char* funcName) {
    // null checking
    if (nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    // top should be a table
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err)) {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err,funcName);
#endif
        ok = false;
    }
    
    if (ok) {
        CCRect r;
        size_t len = lua_objlen(L, lo);
        for (size_t i = 0; i < len; i++) {
            lua_pushnumber(L, i + 1);
            lua_gettable(L, lo);
            if(lua_istable(L, -1)) {
                luaval_to_rect(L, -1, &r);
                ret->push_back(r);
            } else {
                CCAssert(false, "table is needed");
            }
            
            lua_pop(L, 1);
        }
    }
    
    return ok;
}

void point_array_to_luaval(lua_State* L,const cocos2d::CCPoint* points, int count)
{
    if (nullptr  == L)
        return;
    lua_newtable(L);
    for (int i = 1; i <= count; ++i)
    {
        lua_pushnumber(L, i);
        point_to_luaval(L, points[i-1]);
        lua_rawset(L, -3);
    }
}

void aabb_to_luaval(lua_State* L, const cocos2d::ccAABB& r) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "min");
    point_to_luaval(L, r.min);
    lua_rawset(L, -3);
    lua_pushstring(L, "max");
    point_to_luaval(L, r.max);
    lua_rawset(L, -3);
}

void packetheader_to_luaval(lua_State* L, const cocos2d::ccPacketHeader& r) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "magic");
    lua_pushinteger(L, (lua_Integer)*(int*)r.magic);
    lua_rawset(L, -3);
    lua_pushstring(L, "protocolVersion");
    lua_pushinteger(L, (lua_Integer)r.protocolVersion);
    lua_rawset(L, -3);
    lua_pushstring(L, "serverVersion");
    lua_pushinteger(L, (lua_Integer)r.serverVersion);
    lua_rawset(L, -3);
    lua_pushstring(L, "command");
    lua_pushinteger(L, (lua_Integer)r.command);
    lua_rawset(L, -3);
    lua_pushstring(L, "encryptAlgorithm");
    lua_pushinteger(L, (lua_Integer)r.encryptAlgorithm);
    lua_rawset(L, -3);
    lua_pushstring(L, "length");
    lua_pushinteger(L, (lua_Integer)r.length);
    lua_rawset(L, -3);
}

void quad3_to_luaval(lua_State* L, const cocos2d::ccQuad3& q) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "bl");
    vertex3f_to_luaval(L, q.bl);
    lua_rawset(L, -3);
    lua_pushstring(L, "br");
    vertex3f_to_luaval(L, q.br);
    lua_rawset(L, -3);
    lua_pushstring(L, "tl");
    vertex3f_to_luaval(L, q.tl);
    lua_rawset(L, -3);
    lua_pushstring(L, "tr");
    vertex3f_to_luaval(L, q.tr);
    lua_rawset(L, -3);
}

void vertex2f_to_luaval(lua_State* L, const cocos2d::ccVertex2F& v) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushnumber(L, (lua_Number)v.x);
    lua_rawset(L, -3);
    lua_pushstring(L, "y");
    lua_pushnumber(L, (lua_Number)v.y);
    lua_rawset(L, -3);
}

void vertex3f_to_luaval(lua_State* L, const cocos2d::ccVertex3F& v) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushnumber(L, (lua_Number)v.x);
    lua_rawset(L, -3);
    lua_pushstring(L, "y");
    lua_pushnumber(L, (lua_Number)v.y);
    lua_rawset(L, -3);
    lua_pushstring(L, "z");
    lua_pushnumber(L, (lua_Number)v.z);
    lua_rawset(L, -3);
}

void position_to_luaval(lua_State* L, const cocos2d::ccPosition& pos) {
    if (nullptr == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "x");                             /* L: table key */
    lua_pushinteger(L, (lua_Integer)pos.x);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "y");                             /* L: table key */
    lua_pushinteger(L, (lua_Integer)pos.y);               /* L: table key value*/
    lua_rawset(L, -3);
}

void bezierconfig_to_luaval(lua_State* L, const cocos2d::ccBezierConfig& bc) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "endPosition");
    point_to_luaval(L, bc.endPosition);
    lua_rawset(L, -3);
    lua_pushstring(L, "controlPoint_1");
    point_to_luaval(L, bc.controlPoint_1);
    lua_rawset(L, -3);
    lua_pushstring(L, "controlPoint_2");
    point_to_luaval(L, bc.controlPoint_2);
    lua_rawset(L, -3);
}

void csize_to_luaval(lua_State* L, const cocos2d::ccSize& s) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "width");
    lua_pushnumber(L, (lua_Number)s.width);
    lua_rawset(L, -3);
    lua_pushstring(L, "height");
    lua_pushnumber(L, (lua_Number)s.height);
    lua_rawset(L, -3);
}

void cpoint_to_luaval(lua_State* L, const cocos2d::ccPoint& p) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "x");
    lua_pushnumber(L, (lua_Number)p.x);
    lua_rawset(L, -3);
    lua_pushstring(L, "y");
    lua_pushnumber(L, (lua_Number)p.y);
    lua_rawset(L, -3);
}

void v2fc4bt2f_to_luaval(lua_State* L, const cocos2d::ccV2F_C4B_T2F& t) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "vertices");
    vertex2f_to_luaval(L, t.vertices);
    lua_rawset(L, -3);
    lua_pushstring(L, "colors");
    color4b_to_luaval(L, t.colors);
    lua_rawset(L, -3);
    lua_pushstring(L, "texCoords");
    tex2f_to_luaval(L, t.texCoords);
    lua_rawset(L, -3);
}

void v3fc4bt2f_to_luaval(lua_State* L, const cocos2d::ccV3F_C4B_T2F& t) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "vertices");
    vertex3f_to_luaval(L, t.vertices);
    lua_rawset(L, -3);
    lua_pushstring(L, "colors");
    color4b_to_luaval(L, t.colors);
    lua_rawset(L, -3);
    lua_pushstring(L, "texCoords");
    tex2f_to_luaval(L, t.texCoords);
    lua_rawset(L, -3);
}

void v2fc4bt2fquad_to_luaval(lua_State* L, const cocos2d::ccV2F_C4B_T2F_Quad& t) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "bl");
    v2fc4bt2f_to_luaval(L, t.bl);
    lua_rawset(L, -3);
    lua_pushstring(L, "br");
    v2fc4bt2f_to_luaval(L, t.br);
    lua_rawset(L, -3);
    lua_pushstring(L, "tl");
    v2fc4bt2f_to_luaval(L, t.tl);
    lua_rawset(L, -3);
    lua_pushstring(L, "tr");
    v2fc4bt2f_to_luaval(L, t.tr);
    lua_rawset(L, -3);
}

void v3fc4bt2fquad_to_luaval(lua_State* L, const cocos2d::ccV3F_C4B_T2F_Quad& t) {
    if (nullptr == L)
        return;
    lua_newtable(L);
    lua_pushstring(L, "bl");
    v3fc4bt2f_to_luaval(L, t.bl);
    lua_rawset(L, -3);
    lua_pushstring(L, "br");
    v3fc4bt2f_to_luaval(L, t.br);
    lua_rawset(L, -3);
    lua_pushstring(L, "tl");
    v3fc4bt2f_to_luaval(L, t.tl);
    lua_rawset(L, -3);
    lua_pushstring(L, "tr");
    v3fc4bt2f_to_luaval(L, t.tr);
    lua_rawset(L, -3);
}

void tex2f_to_luaval(lua_State* L, const cocos2d::ccTex2F& t) {
    if (nullptr == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "u");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)t.u);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "v");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)t.v);               /* L: table key value*/
    lua_rawset(L, -3);
}

void point_to_luaval(lua_State* L,const cocos2d::CCPoint& vec2)
{
    if (nullptr == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "x");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) vec2.x);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "y");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) vec2.y);               /* L: table key value*/
    lua_rawset(L, -3);
}

void size_to_luaval(lua_State* L,const CCSize& sz)
{
    if (nullptr == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "width");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) sz.width);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "height");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) sz.height);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void crect_to_luaval(lua_State* L, const cocos2d::ccRect& r) {
    if (nullptr == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "x");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)r.x);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "y");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)r.y);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "width");                         /* L: table key */
    lua_pushnumber(L, (lua_Number)r.width);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "height");                        /* L: table key */
    lua_pushnumber(L, (lua_Number)r.height);          /* L: table key value*/
    lua_rawset(L, -3);
}

void rect_to_luaval(lua_State* L,const CCRect& rt)
{
    if (nullptr  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "x");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.origin.x);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "y");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.origin.y);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "width");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.size.width);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "height");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) rt.size.height);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void color4b_to_luaval(lua_State* L,const ccColor4B& cc)
{
    if (nullptr  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "a");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.a);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void colorhsv_to_luaval(lua_State* L,const ccColorHSV& cc) {
    if (nullptr  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "h");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)cc.h);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "s");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)cc.s);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "v");                         /* L: table key */
    lua_pushnumber(L, (lua_Number)cc.v);           /* L: table key value*/
    lua_rawset(L, -3);
}

void color4f_to_luaval(lua_State* L,const ccColor4F& cc)
{
    if (nullptr  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                         /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "a");                        /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.a);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void color3b_to_luaval(lua_State* L,const ccColor3B& cc)
{
    if (nullptr  == L)
        return;
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "r");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.r);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "g");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.g);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) cc.b);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void affinetransform_to_luaval(lua_State* L,const CCAffineTransform& inValue)
{
    if (nullptr  == L)
        return;
    
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "a");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.a);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "b");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.b);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "c");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.c);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "d");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.d);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "tx");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.d);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "ty");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.d);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
}

void fontdefinition_to_luaval(lua_State* L,const ccFontDefinition& inValue)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);                                    /* L: table */
    lua_pushstring(L, "fontName");                      /* L: table key */
    tolua_pushcppstring(L, inValue.m_fontName);          /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontSize");                      /* L: table key */
    lua_pushnumber(L,(lua_Number)inValue.m_fontSize);                 /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontAlignmentH");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.m_alignment);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontAlignmentV");                             /* L: table key */
    lua_pushnumber(L, (lua_Number) inValue.m_vertAlignment);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontFillColor");                             /* L: table key */
    color3b_to_luaval(L, inValue.m_fontFillColor);               /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "fontDimensions");                             /* L: table key */
    size_to_luaval(L, inValue.m_dimensions);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    //Shadow
    lua_pushstring(L, "shadowEnabled");                             /* L: table key */
    lua_pushboolean(L, inValue.m_shadow.m_shadowEnabled);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "shadowOffset");                             /* L: table key */
    size_to_luaval(L, inValue.m_shadow.m_shadowOffset);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "shadowBlur");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue.m_shadow.m_shadowBlur);  /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "shadowOpacity");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue.m_shadow.m_shadowOpacity);  /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    //Stroke
    lua_pushstring(L, "shadowEnabled");                             /* L: table key */
    lua_pushboolean(L, inValue.m_stroke.m_strokeEnabled);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "strokeColor");                             /* L: table key */
    color3b_to_luaval(L, inValue.m_stroke.m_strokeColor);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "strokeSize");                             /* L: table key */
    lua_pushnumber(L, (lua_Number)inValue.m_stroke.m_strokeSize);              /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    
    lua_pushstring(L, "shadowColor");
    lua_pushinteger(L, (lua_Integer)inValue.m_shadowColor);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "lineSpacing");
    lua_pushnumber(L, (lua_Number)inValue.m_lineSpacing);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "globalImageScaleFactor");
    lua_pushnumber(L, (lua_Number)inValue.m_globalImageScaleFactor);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "toCharIndex");
    lua_pushinteger(L, (lua_Integer)inValue.m_toCharIndex);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "decryptFunc");
    lua_pushlightuserdata(L, (void*)inValue.decryptFunc);
    lua_rawset(L, -3);
    
    lua_pushstring(L, "elapsed");
    lua_pushnumber(L, (lua_Number)inValue.m_elapsed);
    lua_rawset(L, -3);
}

void array_to_luaval(lua_State* L,CCArray* inValue)
{
    lua_newtable(L);
    
    if (nullptr == L || nullptr == inValue)
        return;
    
    CCObject* obj = nullptr;
    
    std::string className = "";
    CCString* strVal = nullptr;
    CCDictionary* dictVal = nullptr;
    CCArray* arrVal = nullptr;
    CCDouble* doubleVal = nullptr;
    CCBool* boolVal = nullptr;
    CCFloat* floatVal = nullptr;
    CCInteger* intVal = nullptr;
    int indexTable = 1;
    
    CCARRAY_FOREACH(inValue, obj)
    {
        if (nullptr == obj)
            continue;
        
        std::string typeName = typeid(*obj).name();
        auto iter = g_luaType.find(typeName);
        if (g_luaType.end() != iter)
        {
            className = iter->second;
            if (nullptr != dynamic_cast<cocos2d::CCObject *>(obj))
            {
                lua_pushnumber(L, (lua_Number)indexTable);                
                int ID = (obj) ? (int)obj->m_uID : -1;
                int* luaID = (obj) ? &obj->m_nLuaID : nullptr;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)obj,className.c_str());
                lua_rawset(L, -3);
                CC_SAFE_RETAIN(obj);
                ++indexTable;
            }
        }
        else if((strVal = dynamic_cast<CCString *>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushstring(L, strVal->getCString());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else if ((dictVal = dynamic_cast<CCDictionary*>(obj)))
        {
            dictionary_to_luaval(L, dictVal);
        }
        else if ((arrVal = dynamic_cast<CCArray*>(obj)))
        {
            array_to_luaval(L, arrVal);
        }
        else if ((doubleVal = dynamic_cast<CCDouble*>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushnumber(L, (lua_Number)doubleVal->getValue());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else if ((floatVal = dynamic_cast<CCFloat*>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushnumber(L, (lua_Number)floatVal->getValue());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else if ((intVal = dynamic_cast<CCInteger*>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushinteger(L, (lua_Integer)intVal->getValue());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else if ((boolVal = dynamic_cast<CCBool*>(obj)))
        {
            lua_pushnumber(L, (lua_Number)indexTable);   
            lua_pushboolean(L, boolVal->getValue());
            lua_rawset(L, -3);
            ++indexTable;
        }
        else
        {
            CCAssert(false, "the type isn't suppored.");
        }
    }
}

void dictionary_to_luaval(lua_State* L, CCDictionary* dict)
{
    lua_newtable(L);
    
    if (nullptr == L || nullptr == dict)
        return;
    
    CCDictElement* element = nullptr;
    
    std::string className = "";
    CCString* strVal = nullptr;
    CCDictionary* dictVal = nullptr;
    CCArray* arrVal = nullptr;
    CCDouble* doubleVal = nullptr;
    CCBool* boolVal = nullptr;
    CCFloat* floatVal = nullptr;
    CCInteger* intVal = nullptr;
    
    CCDICT_FOREACH(dict, element)
    {
        if (nullptr == element)
            continue;
        
        std::string typeName = typeid(element->getObject()).name();
        
        auto iter = g_luaType.find(typeName);
        if (g_luaType.end() != iter)
        {
            className = iter->second;
            if ( nullptr != dynamic_cast<CCObject*>(element->getObject()))
            {
                lua_pushstring(L, element->getStrKey());
                int ID = (element->getObject()) ? (int)element->getObject()->m_uID : -1;
                int* luaID = (element->getObject()) ? &(element->getObject()->m_nLuaID) : nullptr;
                toluafix_pushusertype_ccobject(L, ID, luaID, (void*)element->getObject(),className.c_str());
                lua_rawset(L, -3);
                CC_SAFE_RETAIN(element->getObject());
            }
        }
        else if((strVal = dynamic_cast<CCString *>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushstring(L, strVal->getCString());
            lua_rawset(L, -3);
        }
        else if ((dictVal = dynamic_cast<CCDictionary*>(element->getObject())))
        {
            dictionary_to_luaval(L, dictVal);
        }
        else if ((arrVal = dynamic_cast<CCArray*>(element->getObject())))
        {
            array_to_luaval(L, arrVal);
        }
        else if ((doubleVal = dynamic_cast<CCDouble*>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushnumber(L, (lua_Number)doubleVal->getValue());
            lua_rawset(L, -3);
        }
        else if ((floatVal = dynamic_cast<CCFloat*>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushnumber(L, (lua_Number)floatVal->getValue());
            lua_rawset(L, -3);
        }
        else if ((intVal = dynamic_cast<CCInteger*>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushinteger(L, (lua_Integer)intVal->getValue());
            lua_rawset(L, -3);
        }
        else if ((boolVal = dynamic_cast<CCBool*>(element->getObject())))
        {
            lua_pushstring(L, element->getStrKey());
            lua_pushboolean(L, boolVal->getValue());
            lua_rawset(L, -3);
        }
        else
        {
            CCAssert(false, "the type isn't suppored.");
        }
    }
}

void blendfunc_to_luaval(lua_State* L, const cocos2d::ccBlendFunc& func)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);                                    /* L: table */
    
    lua_pushstring(L, "src");                           /* L: table key */
    lua_pushnumber(L, (lua_Number) func.src);           /* L: table key value*/
    lua_rawset(L, -3);                                  /* table[key] = value, L: table */
    lua_pushstring(L, "dst");                           /* L: table key */
    lua_pushnumber(L, (lua_Number) func.dst);           /* L: table key value*/
    lua_rawset(L, -3);
}

void ccvector_std_string_to_luaval(lua_State* L, const std::vector<std::string>& inValue)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    
    int index = 1;
    
    for (const std::string& value : inValue)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushstring(L, value.c_str());
        lua_rawset(L, -3);
        ++index;
    }
}

void ccvector_int_to_luaval(lua_State* L, const std::vector<int>& inValue)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    
    int index = 1;
    for (const int value : inValue)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushnumber(L, (lua_Number)value);
        lua_rawset(L, -3);
        ++index;
    }
}

void ccvector_float_to_luaval(lua_State* L, const std::vector<float>& inValue)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    
    int index = 1;
    for (const float value : inValue)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushnumber(L, (lua_Number)value);
        lua_rawset(L, -3);
        ++index;
    }
}

void ccvector_ushort_to_luaval(lua_State* L, const std::vector<unsigned short>& inValue)
{
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    
    int index = 1;
    for (const unsigned short value : inValue)
    {
        lua_pushnumber(L, (lua_Number)index);
        lua_pushnumber(L, (lua_Number)value);
        lua_rawset(L, -3);
        ++index;
    }
}

void ccvector_rect_to_luaval(lua_State* L, const std::vector<cocos2d::CCRect>& inValue) {
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    
    int index = 1;
    for (const CCRect& value : inValue) {
        lua_pushnumber(L, (lua_Number)index);
        rect_to_luaval(L, value);
        lua_rawset(L, -3);
        ++index;
    }
}

void mat4_to_luaval(lua_State* L, const kmMat4& mat) {
    if (nullptr == L)
        return;
    
    lua_newtable(L);                                    /* L: table */
    for (int i = 0; i < 16; i++) {
        lua_pushnumber(L, i + 1);
        lua_pushnumber(L, (lua_Number)mat.mat[i]);
        lua_rawset(L, -3);
    }
}

void customuniformvalue_to_luaval(lua_State* L, const ccCustomUniformValue& v) {
    if (nullptr == L)
        return;
    
    lua_newtable(L);
    
    // type
    lua_pushstring(L, "type");
    lua_pushnumber(L, (lua_Number)v.type);
    lua_rawset(L, -3);
    
    // based on type
    switch (v.type) {
        case kCCShader_blur:
            lua_pushstring(L, "nodeSize");
            csize_to_luaval(L, v.blur.nodeSize);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "blurSize");
            csize_to_luaval(L, v.blur.blurSize);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "subtract");
            color4f_to_luaval(L, v.blur.subtract);
            lua_rawset(L, -3);
            break;
        case kCCShader_flash:
            lua_pushstring(L, "r");
            lua_pushnumber(L, (lua_Number)v.flash.r);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "g");
            lua_pushnumber(L, (lua_Number)v.flash.g);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "b");
            lua_pushnumber(L, (lua_Number)v.flash.b);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "t");
            lua_pushnumber(L, (lua_Number)v.flash.t);
            lua_rawset(L, -3);
            break;
        case kCCShader_lighting:
            lua_pushstring(L, "mul");
            color4b_to_luaval(L, v.lighting.mul);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "add");
            color3b_to_luaval(L, v.lighting.add);
            lua_rawset(L, -3);
            break;
        case kCCShader_matrix:
            lua_pushstring(L, "mat4");
            mat4_to_luaval(L, v.matrix.mat4);
            lua_rawset(L, -3);
            break;
        case kCCShader_shine:
            lua_pushstring(L, "width");
            lua_pushnumber(L, (lua_Number)v.shine.width);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "time");
            lua_pushnumber(L, (lua_Number)v.shine.time);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "color1");
            color4b_to_luaval(L, v.shine.color1);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "color2");
            color4b_to_luaval(L, v.shine.color2);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "color3");
            color4b_to_luaval(L, v.shine.color3);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "lb");
            cpoint_to_luaval(L, v.shine.lb);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "rt");
            cpoint_to_luaval(L, v.shine.rt);
            lua_rawset(L, -3);
            
            lua_pushstring(L, "gradientPositions");
            vertex3f_to_luaval(L, v.shine.gradientPositions);
            lua_rawset(L, -3);
            break;
        default:
            break;
    }
}

const char* getLuaTypeNameByTypeId(const string& typeName) {
    auto iter = g_luaType.find(typeName);
    if(g_luaType.end() != iter) {
        return iter->second.c_str();
    } else {
        return "CCObject";
    }
}