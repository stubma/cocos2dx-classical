
#ifndef __TOLUA_FIX_H_
#define __TOLUA_FIX_H_

#include "tolua++.h"

#ifdef __cplusplus
extern "C" {
#endif
    
#define TOLUA_REFID_PTR_MAPPING "toluafix_refid_ptr_mapping"
#define TOLUA_REFID_TYPE_MAPPING "toluafix_refid_type_mapping"
#define TOLUA_REFID_FUNCTION_MAPPING "toluafix_refid_function_mapping"
#define TOLUA_REFID_TABLE_MAPPING "toluafix_refid_table_mapping"
    
TOLUA_API void toluafix_open(lua_State* L);
TOLUA_API int toluafix_pushusertype_ccobject(lua_State *L,
                                             int refid,
                                             int *p_refid,
                                             void *vptr,
                                             const char *vtype);
TOLUA_API int toluafix_remove_ccobject_by_refid(lua_State* L, int refid);
TOLUA_API int toluafix_ref_function(lua_State* L, int lo, int def);
TOLUA_API void toluafix_get_function_by_refid(lua_State* L, int refid);
TOLUA_API void toluafix_remove_function_by_refid(lua_State* L, int refid);
TOLUA_API void toluafix_add_type_mapping(unsigned int type, const char* clsName);
TOLUA_API int toluafix_ref_table(lua_State* L, int lo, int def);
TOLUA_API void toluafix_get_table_by_refid(lua_State* L, int refid);
TOLUA_API void toluafix_remove_table_by_refid(lua_State* L, int refid);
    
#ifdef __cplusplus
} // extern "C"
#endif

#endif // __TOLUA_FIX_H_
