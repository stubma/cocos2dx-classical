## ===== instance function implementation template
#set signature = "lua_" + $target_module_fullname + "_" + $class_name + "_" + $func_name
#if $target_module
    #set lua_type = $target_module + "." + $class_name
#else
    #set lua_type = $class_name
#end if
int ${signature}(lua_State* tolua_S) {
    // variables
    int argc = 0;
    ${qualified_name}* cobj = nullptr;
    bool ok = true;
\#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
\#endif

#if not $is_constructor
    // if not constructor, validate the top is our desired object type
\#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "${lua_type}", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function '${signature}'.", &tolua_err);
        return 0;
    }
\#endif
    cobj = (${qualified_name}*)tolua_tousertype(tolua_S, 1, 0);
\#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function '${signature}'", nullptr);
        return 0;
    }
\#endif
#end if

    // get argument count
    argc = lua_gettop(tolua_S) - 1;
#if len($arguments) >= $min_args
    #set arg_count = len($arguments)
    #set arg_idx = $min_args
    #while $arg_idx <= $arg_count

    // if argument count matched, call
    if (argc == ${arg_idx}) {
        #set arg_array = []
        #if $arg_idx > 0
        // arguments declaration
            #set $count = 0
            #while $count < $arg_idx
                #set $arg = $arguments[$count]
        ${arg.decl_in_tpl($generator)} arg${count};
                #set $count = $count + 1
            #end while

        // convert lua value to desired arguments
            #set $count = 0
            #while $count < $arg_idx
                #set $arg = $arguments[$count]
        ${arg.lua_to_native({"generator": $generator,
                             "in_value": "argv[" + str(count) + "]",
                             "out_value": "arg" + str(count),
                             "arg_idx": $count + 2,
                             "class_name": $class_name,
                             "lua_type": $lua_type,
                             "func_name": $func_name,
                             "level": 2,
                             "arg": $arg,
                             "ntype": $arg.qualified_name.replace("*", ""),
                             "arg_lua_type": $generator.to_lua_type($arg.qualified_name, $arg.qualified_ns)})};
                #set $arg_array += ["arg" + str(count)]
                #set $count = $count + 1
            #end while

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function '${signature}'", nullptr);
            return 0;
        }
        #end if

        #set $arg_list = ", ".join($arg_array)
        #if $is_constructor
        // create object, if object is not a CCObject subclass, register gc in lua
        cobj = new ${qualified_name}($arg_list);
            #if $is_ccobject
        int ID = (int)cobj->m_uID ;
        int* luaID = &cobj->m_nLuaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj, "${lua_type}");
            #else
        tolua_pushusertype(tolua_S, (void*)cobj, "${lua_type}");
        tolua_register_gc(tolua_S, lua_gettop(tolua_S));
            #end if
        return 1;
        #else
        // call function
            #if $ret_type.name != "void"
                #if $ret_type.is_enum
        int ret = (int)cobj->${func_name}($arg_list);
                #else
        ${ret_type.whole_decl_in_tpl($generator)} ret = cobj->${func_name}($arg_list);
                #end if
        ${ret_type.lua_from_native({"generator": $generator,
                                    "in_value": "ret",
                                    "out_value": "ret",
                                    "type_name": $ret_type.qualified_name.replace("*", ""),
                                    "ntype": $ret_type.whole_decl_in_tpl($generator),
                                    "class_name": $class_name,
                                    "level": 2,
                                    "arg_lua_type": $generator.to_lua_type($ret_type.qualified_name, $ret_type.qualified_ns)})};
        return 1;
            #else
        cobj->${func_name}($arg_list);
        return 0;
            #end if
        #end if
    }
        #set $arg_idx = $arg_idx + 1
    #end while
#end if

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "${lua_type}:${func_name}", argc, ${min_args});
    return 0;
}

