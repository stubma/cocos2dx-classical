#include "lua_test_auto.h"
#include "test.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

int lua_test_SimpleNativeClass_processInt(lua_State* tolua_S) {
    int argc = 0;
    SimpleNativeClass* cobj = nullptr;
    bool ok = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleNativeClass",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (SimpleNativeClass*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_test_SimpleNativeClass_processInt'", nullptr);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_test_SimpleNativeClass_processInt'.",&tolua_err);
#endif

    return 0;
}

TOLUA_API int register_all_test(lua_State* tolua_S) {
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_test_SimpleNativeClass(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

