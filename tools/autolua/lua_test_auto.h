#ifndef __test_h__
#define __test_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "tolua++.h"

#ifdef __cplusplus
}
#endif

int register_all_test(lua_State* tolua_S);

#endif // __test_h__