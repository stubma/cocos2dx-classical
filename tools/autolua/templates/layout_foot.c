TOLUA_API int register_all_${target_module_fullname}(lua_State* tolua_S) {
	tolua_open(tolua_S);
	
	#if $target_module
	tolua_module(tolua_S,"${target_module}",0);
	tolua_beginmodule(tolua_S,"${target_module}");
	#else
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);
	#end if

	#for jsclass in $generated_classes
	lua_register_${target_module_fullname}_${jsclass}(tolua_S);
	#end for

	tolua_endmodule(tolua_S);
	return 1;
}

