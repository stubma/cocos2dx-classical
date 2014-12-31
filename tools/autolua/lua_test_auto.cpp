#include "lua_test_auto.h"
#include "test.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

int lua_test_SimpleNativeClass_processInt(lua_State* tolua_S) {
    // variables
    int argc = 0;
    SimpleNativeClass* cobj = nullptr;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "SimpleNativeClass", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_test_SimpleNativeClass_processInt'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (SimpleNativeClass*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_test_SimpleNativeClass_processInt'", nullptr);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // try call function
    do {
        if (argc == 2) {
            // arguments declaration
            std::string arg0;
            CCPoint arg1;

            // convert lua value to desired arguments
            ok &= luaval_to_std_string(tolua_S, 2, &arg0, "SimpleNativeClass:processInt");
            ok &= luaval_to_point(tolua_S, 3, &arg1, "SimpleNativeClass:processInt");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            int ret = SimpleNativeClass::processInt(arg0, arg1);
            tolua_pushnumber(tolua_S, (lua_Number)ret);
            return 1;
        }
    } while(0);
    ok = true;

    // try call function
    do {
        if (argc == 3) {
            // arguments declaration
            std::string arg0;
            CCPoint arg1;
            double arg2;

            // convert lua value to desired arguments
            ok &= luaval_to_std_string(tolua_S, 2, &arg0, "SimpleNativeClass:processInt");
            ok &= luaval_to_point(tolua_S, 3, &arg1, "SimpleNativeClass:processInt");
            ok &= luaval_to_number(tolua_S, 4, &arg2, "SimpleNativeClass:processInt");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            int ret = SimpleNativeClass::processInt(arg0, arg1, arg2);
            tolua_pushnumber(tolua_S, (lua_Number)ret);
            return 1;
        }
    } while(0);
    ok = true;

    // try call function
    do {
        if (argc == 1) {
            // arguments declaration
            std::string arg0;

            // convert lua value to desired arguments
            ok &= luaval_to_std_string(tolua_S, 2, &arg0, "SimpleNativeClass:processInt");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            SimpleNativeClass::processInt(arg0);
            return 0;
        }
    } while(0);
    ok = true;

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "SimpleNativeClass:processInt",argc, 1);
    return 0;
}

int lua_test_SimpleNativeClass_SimpleNativeClass(lua_State* tolua_S) {
    // variables
    int argc = 0;
    SimpleNativeClass* cobj = nullptr;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // create object, if object is a CCObject subclass, autorelease it
        // if not, register gc in lua
        cobj = new SimpleNativeClass();
        tolua_pushusertype(tolua_S, (void*)cobj, "SimpleNativeClass");
        tolua_register_gc(tolua_S, lua_gettop(tolua_S));
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SimpleNativeClass:SimpleNativeClass", argc, 0);
    return 0;
}

TOLUA_API int register_all_test(lua_State* tolua_S) {
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_test_SimpleNativeClass(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

