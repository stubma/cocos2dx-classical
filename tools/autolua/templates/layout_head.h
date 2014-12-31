\#ifndef __${target_module_fullname}_h__
\#define __${target_module_fullname}_h__

\#ifdef __cplusplus
extern "C" {
\#endif

\#include "tolua++.h"

\#ifdef __cplusplus
}
\#endif

int register_all_${target_module_fullname}(lua_State* tolua_S);
