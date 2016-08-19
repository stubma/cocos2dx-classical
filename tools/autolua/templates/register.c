#if $target_module
    #set lua_type = $target_module + "." + $class_name
#else
    #set lua_type = $class_name
#end if
int lua_register_${target_module_fullname}_${class_name}(lua_State* tolua_S) {
    tolua_usertype(tolua_S, "${lua_type}");
#if len($parents) > 0
    tolua_class(tolua_S, "${class_name}", "${generator.to_lua_type($parents[0].qualified_name, $parents[0].qualified_ns)}", nullptr);
#else
    tolua_class(tolua_S, "${class_name}", "", nullptr);
#end if

    // register module
    tolua_beginmodule(tolua_S, "${class_name}");
#for name, m in $methods.items()
    #if $m.is_constructor
        tolua_function(tolua_S, "new", lua_${target_module_fullname}_${class_name}_${class_name});
    #else if not $m.is_destructor
        tolua_function(tolua_S, "${m.func_name}", lua_${target_module_fullname}_${class_name}_${m.func_name});
    #end if
#end for
#for name, m in $static_methods.items()
        tolua_function(tolua_S, "${m.func_name}", lua_${target_module_fullname}_${class_name}_${m.func_name});
#end for
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(${qualified_name}).name();
    g_luaType[typeName] = "${lua_type}";
    g_typeCast["${class_name}"] = "${lua_type}";
    return 1;
}

