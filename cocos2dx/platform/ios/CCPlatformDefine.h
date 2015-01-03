#ifndef __CCPLATFORMDEFINE_H__
#define __CCPLATFORMDEFINE_H__

#include <assert.h>

#define CC_DLL 

#define CC_ASSERT(cond) assert(cond)

#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define nullptr pointer value */
#ifndef nullptr
    #ifdef __cplusplus
        #define nullptr    0
    #else
        #define nullptr    ((void *)0)
    #endif
#endif

#endif /* __CCPLATFORMDEFINE_H__*/
