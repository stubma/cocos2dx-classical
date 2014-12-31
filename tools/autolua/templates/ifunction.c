## ===== instance function implementation template
int lua_${target_module_fullname}_${class_name}_${func_name}(lua_State* tolua_S) {
    int argc = 0;
    ${qualified_name}* cobj = nullptr;
    bool ok = true;

\#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
\#endif

    // if not constructor, validate the top is our desired object type
#if not $is_constructor
\#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"${target_module}.${class_name}",0,&tolua_err)) goto tolua_lerror;
\#endif
    cobj = (${qualified_name}*)tolua_tousertype(tolua_S,1,0);
\#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_${target_module_fullname}_${class_name}_${func_name}'", nullptr);
        return 0;
    }
\#endif
#end if

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

\#if COCOS2D_DEBUG >= 1
#if not $is_constructor
    tolua_lerror:
#end if
    tolua_error(tolua_S,"#ferror in function 'lua_${target_module_fullname}_${class_name}_${func_name}'.",&tolua_err);
\#endif

    return 0;
}

