#include "lua_test_auto.h"
#include "test.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

int lua_test_SimpleNativeClass_processInt(lua_State* tolua_S) {
    // variables
    int argc = 0;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S, 1,"SimpleNativeClass", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_test_SimpleNativeClass_processInt'.", &tolua_err);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        cocos2d::CCPoint arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_point(tolua_S, 2, &arg0, "SimpleNativeClass:processInt");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_test_SimpleNativeClass_processInt'", NULL);
            return 0;
        }

        // call function
        SimpleNativeClass::processInt(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SimpleNativeClass:processInt", argc, 1);
    return 0;
}

int lua_register_test_SimpleNativeClass(lua_State* tolua_S) {
    tolua_usertype(tolua_S, "SimpleNativeClass");
    tolua_cclass(tolua_S, "SimpleNativeClass", "SimpleNativeClass", "", NULL);

    // register module
    tolua_beginmodule(tolua_S, "SimpleNativeClass");
        tolua_function(tolua_S, "processInt", lua_test_SimpleNativeClass_processInt);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(SimpleNativeClass).name();
    g_luaType[typeName] = "SimpleNativeClass";
    g_typeCast["SimpleNativeClass"] = "SimpleNativeClass";
    return 1;
}

TOLUA_API int register_all_test(lua_State* tolua_S) {
	tolua_open(tolua_S);
	
	tolua_module(tolua_S, NULL, 0);
	tolua_beginmodule(tolua_S, NULL);

	lua_register_test_SimpleNativeClass(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

