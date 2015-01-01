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
#ifndef __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
#define __COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__

extern "C" {
#include "lua.h"
#include "tolua++.h"
}
#include "tolua_fix.h"
#include "cocos2d.h"

using namespace cocos2d;

extern std::map<std::string, std::string>  g_luaType;
extern std::map<std::string, std::string>  g_typeCast;

#if COCOS2D_DEBUG >=1
void luaval_to_native_err(lua_State* L,const char* msg,tolua_Error* err, const char* funcName = "");
#endif

#define LUA_PRECONDITION( condition, ...) if( ! (condition) ) {														\
CCLOG("lua: ERROR: File %s: Line: %d, Function: %s", __FILE__, __LINE__, __FUNCTION__ );                                                         \
CCLOG(__VA_ARGS__);                                                  \
}                                                                           \

extern bool luaval_is_usertype(lua_State* L,int lo,const char* type, int def);
// to native
extern bool luaval_to_ulong(lua_State* L,int lo, unsigned long* outValue, const char* funcName="");
extern bool luaval_to_ushort(lua_State* L, int lo, unsigned short* outValue, const char* funcName = "");
extern bool luaval_to_int32(lua_State* L,int lo,int* outValue, const char* funcName = "");
extern bool luaval_to_uint32(lua_State* L, int lo, unsigned int* outValue, const char* funcName = "");
extern bool luaval_to_uint16(lua_State* L,int lo,uint16_t* outValue, const char* funcName = "");
extern bool luaval_to_boolean(lua_State* L,int lo,bool* outValue, const char* funcName = "");
extern bool luaval_to_number(lua_State* L,int lo,double* outValue, const char* funcName = "");
extern bool luaval_to_long_long(lua_State* L,int lo,long long* outValue, const char* funcName = "");
extern bool luaval_to_std_string(lua_State* L, int lo, std::string* outValue, const char* funcName = "");
extern bool luaval_to_long(lua_State* L,int lo, long* outValue, const char* funcName = "");
extern bool luaval_to_ssize(lua_State* L,int lo, ssize_t* outValue, const char* funcName = "");
extern bool luaval_to_size(lua_State* L,int lo, CCSize* outValue, const char* funcName = "");
extern bool luaval_to_rect(lua_State* L,int lo, CCRect* outValue, const char* funcName = "");
extern bool luaval_to_color3b(lua_State* L,int lo, ccColor3B* outValue, const char* funcName = "");
extern bool luaval_to_color4b(lua_State* L,int lo, ccColor4B* outValue, const char* funcName = "");
extern bool luaval_to_color4f(lua_State* L,int lo, ccColor4F* outValue, const char* funcName = "");
extern bool luaval_to_affinetransform(lua_State* L,int lo, CCAffineTransform* outValue, const char* funcName = "");
extern bool luaval_to_fontdefinition(lua_State* L, int lo, ccFontDefinition* outValue , const char* funcName = "");
extern bool luaval_to_array(lua_State* L,int lo, CCArray** outValue, const char* funcName = "");
extern bool luaval_to_dictionary(lua_State* L,int lo, CCDictionary** outValue, const char* funcName = "");
extern bool luaval_to_array_of_point(lua_State* L,int lo,cocos2d::CCPoint **points, int *numPoints, const char* funcName = "");
extern bool luavals_variadic_to_array(lua_State* L,int argc, CCArray** ret);
extern bool luaval_to_point(lua_State* L,int lo,cocos2d::CCPoint* outValue, const char* funcName = "");
extern bool luaval_to_blendfunc(lua_State* L, int lo, cocos2d::ccBlendFunc* outValue, const char* funcName = "");
extern bool luaval_to_position(lua_State* L, int lo, cocos2d::ccPosition* outValue, const char* funcName = "");
extern bool luaval_to_vertex3f(lua_State* L, int lo, cocos2d::ccVertex3F* outValue, const char* funcName = "");
extern bool luaval_to_bezierconfig(lua_State* L, int lo, cocos2d::ccBezierConfig* outValue, const char* funcName = "");
extern bool luaval_to_quad3(lua_State* L, int lo, cocos2d::ccQuad3* outValue, const char* funcName = "");
extern bool luaval_to_cpoint(lua_State* L, int lo, cocos2d::ccPoint* outValue, const char* funcName = "");
extern bool luaval_to_crect(lua_State* L, int lo, cocos2d::ccRect* outValue, const char* funcName = "");

bool luaval_to_std_vector_string(lua_State* L, int lo, std::vector<std::string>* ret, const char* funcName = "");
bool luaval_to_std_vector_int(lua_State* L, int lo, std::vector<int>* ret, const char* funcName = "");

template <class T>
bool luaval_to_object(lua_State* L, int lo, const char* type, T** ret)
{
    if(NULL == L || lua_gettop(L) < lo)
        return false;
    
    if (!luaval_is_usertype(L, lo, type, 0))
        return false;
    
    *ret = static_cast<T*>(tolua_tousertype(L, lo, 0));
    
    if (NULL == ret)
        LUA_PRECONDITION(ret, "Invalid Native Object");
    
    return true;
}

extern bool luaval_to_std_vector_float(lua_State* L, int lo, std::vector<float>* ret, const char* funcName = "");
extern bool luaval_to_std_vector_ushort(lua_State* L, int lo, std::vector<unsigned short>* ret, const char* funcName = "");

// from native
extern void point_to_luaval(lua_State* L,const cocos2d::CCPoint& vec2);
extern void point_array_to_luaval(lua_State* L,const cocos2d::CCPoint* points, int count);
extern void size_to_luaval(lua_State* L,const CCSize& sz);
extern void rect_to_luaval(lua_State* L,const CCRect& rt);
extern void color3b_to_luaval(lua_State* L,const ccColor3B& cc);
extern void color4b_to_luaval(lua_State* L,const ccColor4B& cc);
extern void color4f_to_luaval(lua_State* L,const ccColor4F& cc);
extern void affinetransform_to_luaval(lua_State* L,const CCAffineTransform& inValue);
extern void fontdefinition_to_luaval(lua_State* L,const ccFontDefinition& inValue);
extern void array_to_luaval(lua_State* L, CCArray* inValue);
extern void dictionary_to_luaval(lua_State* L, CCDictionary* dict);
extern void blendfunc_to_luaval(lua_State* L, const cocos2d::ccBlendFunc& func);
extern void position_to_luaval(lua_State* L, const cocos2d::ccPosition& pos);
extern void vertex3f_to_luaval(lua_State* L, const cocos2d::ccVertex3F& v);
extern void bezierconfig_to_luaval(lua_State* L, const cocos2d::ccBezierConfig& bc);
extern void quad3_to_luaval(lua_State* L, const cocos2d::ccQuad3& q);
extern void cpoint_to_luaval(lua_State* L, const cocos2d::ccPoint& p);
extern void crect_to_luaval(lua_State* L, const cocos2d::ccRect& r);

/**
 Because all override functions wouldn't be bound,so we must use `typeid` to get the real class name
 */
template <class T>
const char* getLuaTypeName(T* ret,const char* type)
{
    if (NULL != ret)
    {
        std::string hashName = typeid(*ret).name();
        auto iter =  g_luaType.find(hashName);
        if(g_luaType.end() != iter)
        {
            return iter->second.c_str();
        }
        else
        {
            return type;
        }
    }
    
    return NULL;
}

template <class T>
void object_to_luaval(lua_State* L,const char* type, T* ret)
{
    if(NULL != ret) {
        cocos2d::CCObject* dynObject = dynamic_cast<cocos2d::CCObject*>(ret);
        if (dynObject) {
            // use c style cast, T may not polymorphic
            cocos2d::CCObject* dynObject = (cocos2d::CCObject*)(ret);
            int ID = (int)(dynObject->m_uID) ;
            int* luaID = &(dynObject->m_nLuaID);
            toluafix_pushusertype_ccobject(L, ID, luaID, (void*)ret,type);
        } else {
            tolua_pushusertype(L, (void*)ret, getLuaTypeName(ret, type));
        }
    } else {
        lua_pushnil(L);
    }
}

void ccvector_std_string_to_luaval(lua_State* L, const std::vector<std::string>& inValue);
void ccvector_int_to_luaval(lua_State* L, const std::vector<int>& inValue);
void ccvector_float_to_luaval(lua_State* L, const std::vector<float>& inValue);
void ccvector_ushort_to_luaval(lua_State* L, const std::vector<unsigned short>& inValue);

#endif //__COCOS2DX_SCRIPTING_LUA_COCOS2DXSUPPORT_LUABAISCCONVERSIONS_H__
