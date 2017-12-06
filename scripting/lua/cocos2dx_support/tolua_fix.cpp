
#include "tolua_fix.h"
#include <stdlib.h>
#include <map>
#include <typeinfo>
#include "cocoa/CCObject.h"
#include "platform/platform.h"

#ifdef __cplusplus
extern "C" {
#endif
    
static int s_function_ref_id = 0;
static int s_table_ref_id = 0;
static std::map<unsigned int, char*> hash_type_mapping;
    
TOLUA_API void toluafix_open(lua_State* L)
{
    lua_pushstring(L, TOLUA_REFID_PTR_MAPPING);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);
    
    lua_pushstring(L, TOLUA_REFID_TYPE_MAPPING);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);

    lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);
    
    lua_pushstring(L, TOLUA_REFID_TABLE_MAPPING);
    lua_newtable(L);
    lua_rawset(L, LUA_REGISTRYINDEX);
}
    
TOLUA_API void toluafix_add_type_mapping(unsigned int type, const char *clsName) {
    if (hash_type_mapping.find(type) == hash_type_mapping.end()) {
        hash_type_mapping[type] = strdup(clsName);
    }
}

TOLUA_API int toluafix_pushusertype_ccobject(lua_State *L,
                                             int refid,
                                             int *p_refid,
                                             void *vptr,
                                             const char *vtype) {
    if (vptr == NULL || p_refid == NULL) {
        lua_pushnil(L);
        return -1;
    }
    
    cocos2d::CCObject *ptr = static_cast<cocos2d::CCObject*>(vptr);
    unsigned int hash = cocos2d::CLASS_HASH_CODE(typeid(*ptr));
    char* type = hash_type_mapping[hash];
    if (type == NULL) {
        // CCLOG("[TOLUA] Unable to find type map for object %s:%p,", vtype, vptr);
    }
    
    if (*p_refid == 0) {
        *p_refid = refid;
        
        lua_pushstring(L, TOLUA_REFID_PTR_MAPPING);
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: refid_ptr */
        lua_pushinteger(L, refid);                                  /* stack: refid_ptr refid */
        lua_pushlightuserdata(L, ptr);                              /* stack: refid_ptr refid ptr */
        
        lua_rawset(L, -3);                  /* refid_ptr[refid] = ptr, stack: refid_ptr */
        lua_pop(L, 1);                                              /* stack: - */
        
        lua_pushstring(L, TOLUA_REFID_TYPE_MAPPING);
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: refid_type */
        lua_pushinteger(L, refid);                                  /* stack: refid_type refid */
        lua_pushstring(L, type ? type : vtype);                     /* stack: refid_type refid type */
        lua_rawset(L, -3);                /* refid_type[refid] = type, stack: refid_type */
        lua_pop(L, 1);                                              /* stack: - */
        
        //printf("[LUA] push CCObject OK - refid: %d, ptr: %x, type: %s\n", *p_refid, (int)ptr, type);
    }
    
    tolua_pushusertype_and_addtoroot(L, ptr, type ? type : vtype);
    return 0;
}
    
TOLUA_API int toluafix_remove_ccobject_by_refid(lua_State* L, int refid)
{
	void* ptr = NULL;
    const char* type = NULL;
    void** ud = NULL;
    if (refid == 0) return -1;
    
    // get ptr from tolua_refid_ptr_mapping
    lua_pushstring(L, TOLUA_REFID_PTR_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                               /* stack: refid_ptr */
    lua_pushinteger(L, refid);                                      /* stack: refid_ptr refid */
    lua_rawget(L, -2);                                              /* stack: refid_ptr ptr */
    ptr = lua_touserdata(L, -1);
    lua_pop(L, 1);                                                  /* stack: refid_ptr */
    if (ptr == NULL)
    {
        lua_pop(L, 1);
        // Lua stack has closed, C++ object not in Lua.
        // printf("[LUA ERROR] remove CCObject with NULL ptr, refid: %d\n", refid);
        return -2;
    }
    
    // remove ptr from tolua_refid_ptr_mapping
    lua_pushinteger(L, refid);                                      /* stack: refid_ptr refid */
    lua_pushnil(L);                                                 /* stack: refid_ptr refid nil */
    lua_rawset(L, -3);                     /* delete refid_ptr[refid], stack: refid_ptr */
    lua_pop(L, 1);                                                  /* stack: - */
    
    
    // get type from tolua_refid_type_mapping
    lua_pushstring(L, TOLUA_REFID_TYPE_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                               /* stack: refid_type */
    lua_pushinteger(L, refid);                                      /* stack: refid_type refid */
    lua_rawget(L, -2);                                              /* stack: refid_type type */
    if (lua_isnil(L, -1))
    {
        lua_pop(L, 2);
        printf("[LUA ERROR] remove CCObject with NULL type, refid: %d, ptr: %p\n", refid, ptr);
        return -1;
    }
    
    type = lua_tostring(L, -1);
    lua_pop(L, 1);                                                  /* stack: refid_type */

    // remove type from tolua_refid_type_mapping
    lua_pushinteger(L, refid);                                      /* stack: refid_type refid */
    lua_pushnil(L);                                                 /* stack: refid_type refid nil */
    lua_rawset(L, -3);                    /* delete refid_type[refid], stack: refid_type */
    lua_pop(L, 1);                                                  /* stack: - */
    
    // get ubox
    luaL_getmetatable(L, type);                                     /* stack: mt */
    lua_pushstring(L, "tolua_ubox");                                /* stack: mt key */
    lua_rawget(L, -2);                                              /* stack: mt ubox */
    if (lua_isnil(L, -1))
    {
        // use global ubox
        lua_pop(L, 1);                                              /* stack: mt */
        lua_pushstring(L, "tolua_ubox");                            /* stack: mt key */
        lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: mt ubox */
    };
    
    
    // cleanup root
    tolua_remove_value_from_root(L, ptr);
    
    lua_pushlightuserdata(L, ptr);                                  /* stack: mt ubox ptr */
    lua_rawget(L,-2);                                               /* stack: mt ubox ud */
    if (lua_isnil(L, -1))
    {
        // Lua object has released (GC), C++ object not in ubox.
        //printf("[LUA ERROR] remove CCObject with NULL ubox, refid: %d, ptr: %x, type: %s\n", refid, (int)ptr, type);
        lua_pop(L, 3);
        return -3;
    }

    // cleanup peertable
    lua_pushvalue(L, TOLUA_NOPEER);
    lua_setfenv(L, -2);

    ud = (void**)lua_touserdata(L, -1);
    lua_pop(L, 1);                                                  /* stack: mt ubox */
    if (ud == NULL)
    {
        printf("[LUA ERROR] remove CCObject with NULL userdata, refid: %d, ptr: %p, type: %s\n", refid, ptr, type);
        lua_pop(L, 2);
        return -1;
    }
    
    // clean userdata
    *ud = NULL;
    
    lua_pushlightuserdata(L, ptr);                                  /* stack: mt ubox ptr */
    lua_pushnil(L);                                                 /* stack: mt ubox ptr nil */
    lua_rawset(L, -3);                             /* ubox[ptr] = nil, stack: mt ubox */
    
    lua_pop(L, 2);
    //printf("[LUA] remove CCObject, refid: %d, ptr: %x, type: %s\n", refid, (int)ptr, type);
    return 0;
}
    
TOLUA_API int toluafix_ref_table(lua_State* L, int lo, int def) {
    // convert lo to positive if it is negative
    if(lo < 0)
        lo = lua_gettop(L) + lo + 1;
    
    // function at lo
    if (!lua_istable(L, lo))
        return 0;
    
    // increase id
    s_table_ref_id++;
    
    // push to ref table
    lua_pushstring(L, TOLUA_REFID_TABLE_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: fun ... refid_t */
    lua_pushinteger(L, s_table_ref_id);                         /* stack: fun ... refid_t refid */
    lua_pushvalue(L, lo);                                       /* stack: fun ... refid_t refid table */

    // set
    lua_rawset(L, -3);                                          /* refid_t[refid] = table, stack: fun ... refid_ptr */
    lua_pop(L, 1);                                              /* stack: fun ... */
    
    return s_table_ref_id;
}

TOLUA_API void toluafix_remove_table_by_refid(lua_State* L, int refid) {
    lua_pushstring(L, TOLUA_REFID_TABLE_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: ... refid_t */
    lua_pushinteger(L, refid);                                  /* stack: ... refid_t refid */
    lua_pushnil(L);                                             /* stack: ... refid_t refid nil */
    lua_rawset(L, -3);                                          /* refid_t[refid] = table, stack: ... refid_ptr */
    lua_pop(L, 1);                                              /* stack: ... */
}
    
TOLUA_API void toluafix_get_table_by_refid(lua_State* L, int refid) {
    lua_pushstring(L, TOLUA_REFID_TABLE_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: ... refid_t */
    lua_pushinteger(L, refid);                                  /* stack: ... refid_t refid */
    lua_rawget(L, -2);                                          /* stack: ... refid_t table */
    lua_remove(L, -2);                                          /* stack: ... table */
}
    
TOLUA_API int toluafix_ref_function(lua_State* L, int lo, int def)
{
    // convert lo to positive if it is negative
    if(lo < 0)
        lo = lua_gettop(L) + lo + 1;
    
    // function at lo
    if (!lua_isfunction(L, lo)) return 0;
    
    s_function_ref_id++;
    
    lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: fun ... refid_fun */
    lua_pushinteger(L, s_function_ref_id);                      /* stack: fun ... refid_fun refid */
    lua_pushvalue(L, lo);                                       /* stack: fun ... refid_fun refid fun */
    
    lua_rawset(L, -3);                  /* refid_fun[refid] = fun, stack: fun ... refid_ptr */
    lua_pop(L, 1);                                              /* stack: fun ... */
    
    return s_function_ref_id;
    
    // lua_pushvalue(L, lo);                                           /* stack: ... func */
    // return luaL_ref(L, LUA_REGISTRYINDEX);
}

TOLUA_API void toluafix_get_function_by_refid(lua_State* L, int refid)
{
    lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: ... refid_fun */
    lua_pushinteger(L, refid);                                  /* stack: ... refid_fun refid */
    lua_rawget(L, -2);                                          /* stack: ... refid_fun fun */
    lua_remove(L, -2);                                          /* stack: ... fun */
}

TOLUA_API void toluafix_remove_function_by_refid(lua_State* L, int refid)
{
    lua_pushstring(L, TOLUA_REFID_FUNCTION_MAPPING);
    lua_rawget(L, LUA_REGISTRYINDEX);                           /* stack: ... refid_fun */
    lua_pushinteger(L, refid);                                  /* stack: ... refid_fun refid */
    lua_pushnil(L);                                             /* stack: ... refid_fun refid nil */
    lua_rawset(L, -3);                  /* refid_fun[refid] = fun, stack: ... refid_ptr */
    lua_pop(L, 1);                                              /* stack: ... */

    // luaL_unref(L, LUA_REGISTRYINDEX, refid);
}

#ifdef __cplusplus
}
#endif
