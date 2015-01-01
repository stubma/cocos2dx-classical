## ===== instance function implementation template - for overloaded functions
#set signature = "lua_" + $target_module_fullname + "_" + $class_name + "_" + $func_name
#if $target_module
    #set lua_type = $target_module + "." + $class_name
#else
    #set lua_type = $class_name
#end if
int ${signature}(lua_State* tolua_S) {
    // variables
    int argc = 0;
    bool ok = true;
\#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
\#endif

    // if not constructor, validate the top is our desired object type
\#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S, 1, "${lua_type}", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function '${signature}'.", &tolua_err);
        return 0;
    }
\#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;
#for func in $implementations
    #if len($func.arguments) >= $func.min_args
        #set arg_count = len($func.arguments)
        #set arg_idx = $func.min_args
        #while $arg_idx <= $arg_count
            #set arg_list = ""
            #set arg_array = []

    // try call function
    do {
        if (argc == ${arg_idx}) {
            #if $func.min_args > 0
            // arguments declaration
                #set $count = 0
                #while $count < $arg_idx
                    #set $arg = $func.arguments[$count]
            ${arg.decl_in_tpl($generator)} arg${count};
                    #set $count = $count + 1
                #end while

            // convert lua value to desired arguments
                #set $count = 0
                #while $count < $arg_idx
                    #set $arg = $func.arguments[$count]
            ${arg.lua_to_native({"generator": $generator,
                                 "in_value": "argv[" + str(count) + "]",
                                 "out_value": "arg" + str(count),
                                 "arg_idx": $count + 2,
                                 "class_name": $class_name,
                                 "lua_type": $lua_type,
                                 "func_name": $func.func_name,
                                 "level": 2,
                                 "arg": $arg,
                                 "ntype": $arg.qualified_name.replace("*", ""),
                                 "arg_lua_type": $generator.to_lua_type($arg.qualified_name, $arg.qualified_ns)})};
                    #set $arg_array += ["arg" + str(count)]
                    #set $count = $count + 1
                #end while

            // if conversion is not ok, print error and return
            if(!ok) { break; }
            #end if

            #set $arg_list = ", ".join($arg_array)
            // call function
            #if $func.ret_type.name != "void"
                #if $func.ret_type.is_enum
            int ret = (int)${qualified_name}::${func.func_name}($arg_list);
                #else
            ${func.ret_type.whole_decl_in_tpl($generator)} ret = ${qualified_name}::${func.func_name}($arg_list);
                #end if
            ${func.ret_type.lua_from_native({"generator": $generator,
                                            "in_value": "ret",
                                            "out_value": "ret",
                                            "type_name": $func.ret_type.qualified_name.replace("*", ""),
                                            "ntype": $func.ret_type.whole_decl_in_tpl($generator),
                                            "class_name": $class_name,
                                            "level": 2,
                                            "arg_lua_type": $generator.to_lua_type($func.ret_type.qualified_name, $func.ret_type.qualified_ns)})};
            return 1;
            #else
            ${qualified_name}::${func.func_name}($arg_list);
            return 0;
            #end if
        }
    } while(0);
            #set $arg_idx = $arg_idx + 1
    ok = true;
        #end while
    #end if
#end for

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "${lua_type}:${func.func_name}",argc, ${func.min_args});
    return 0;
}

