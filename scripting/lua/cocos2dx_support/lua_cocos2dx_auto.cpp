#include "lua_cocos2dx_auto.h"
#include "ccConfig.h"
#include "CCEventType.h"
#include "ccMacros.h"
#include "CCProtocols.h"
#include "ccTypeInfo.h"
#include "ccTypes.h"
#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

int lua_cocos2dx_CCNode_create(lua_State* tolua_S) {
    // variables
    int argc = 0;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S, 1,"CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_create'.", &tolua_err);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCNode* ret = cocos2d::CCNode::create();
        object_to_luaval<cocos2d::CCNode>(tolua_S, "CCNode", (cocos2d::CCNode*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:create", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_addChild(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_addChild'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_addChild'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // try call function
    do {
        if (argc == 2) {
            // arguments declaration
            CCNode* arg0;
            int arg1;

            // convert lua value to desired arguments
            ok &= luaval_to_object<CCNode>(tolua_S, 2, "CCNode", &arg0);
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "CCNode:addChild");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->addChild(arg0, arg1);
            return 0;
        }
    } while(0);
    ok = true;

    // try call function
    do {
        if (argc == 1) {
            // arguments declaration
            CCNode* arg0;

            // convert lua value to desired arguments
            ok &= luaval_to_object<CCNode>(tolua_S, 2, "CCNode", &arg0);

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->addChild(arg0);
            return 0;
        }
    } while(0);
    ok = true;

    // try call function
    do {
        if (argc == 3) {
            // arguments declaration
            CCNode* arg0;
            int arg1;
            int arg2;

            // convert lua value to desired arguments
            ok &= luaval_to_object<CCNode>(tolua_S, 2, "CCNode", &arg0);
            ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "CCNode:addChild");
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "CCNode:addChild");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->addChild(arg0, arg1, arg2);
            return 0;
        }
    } while(0);
    ok = true;

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "CCNode:addChild",argc, 3);
    return 0;
}

int lua_cocos2dx_CCNode_removeComponent(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_removeComponent'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_removeComponent'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCComponent* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCComponent>(tolua_S, 2, "CCComponent", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_removeComponent'", NULL);
            return 0;
        }

        // call function
        bool ret = cobj->removeComponent(arg0);
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:removeComponent", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_nodeToWorldTransform(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_nodeToWorldTransform'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_nodeToWorldTransform'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCAffineTransform ret = cobj->nodeToWorldTransform();
        affinetransform_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:nodeToWorldTransform", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_removeAllComponents(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_removeAllComponents'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_removeAllComponents'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->removeAllComponents();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:removeAllComponents", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getShaderProgram(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getShaderProgram'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getShaderProgram'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCGLProgram* ret = cobj->getShaderProgram();
        object_to_luaval<cocos2d::CCGLProgram>(tolua_S, "CCGLProgram", (cocos2d::CCGLProgram*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getShaderProgram", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getUserObject(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getUserObject'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getUserObject'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCObject* ret = cobj->getUserObject();
        object_to_luaval<cocos2d::CCObject>(tolua_S, "CCObject", (cocos2d::CCObject*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getUserObject", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getChildren(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getChildren'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getChildren'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCArray* ret = cobj->getChildren();
        array_to_luaval(tolua_S,ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getChildren", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getScriptHandler(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getScriptHandler'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getScriptHandler'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        int ret = cobj->getScriptHandler();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getScriptHandler", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_convertToWorldSpaceAR(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_convertToWorldSpaceAR'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_convertToWorldSpaceAR'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCPoint arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_point(tolua_S, 2, &arg0, "CCNode:convertToWorldSpaceAR");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_convertToWorldSpaceAR'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCPoint ret = cobj->convertToWorldSpaceAR(arg0);
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:convertToWorldSpaceAR", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_isIgnoreAnchorPointForPosition(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_isIgnoreAnchorPointForPosition'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_isIgnoreAnchorPointForPosition'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        bool ret = cobj->isIgnoreAnchorPointForPosition();
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:isIgnoreAnchorPointForPosition", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_init(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_init'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_init'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:init", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_setRotation(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setRotation'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setRotation'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setRotation");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setRotation'", NULL);
            return 0;
        }

        // call function
        cobj->setRotation(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setRotation", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setZOrder(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setZOrder'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setZOrder'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:setZOrder");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setZOrder'", NULL);
            return 0;
        }

        // call function
        cobj->setZOrder(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setZOrder", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setScaleY(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setScaleY'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setScaleY'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setScaleY");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setScaleY'", NULL);
            return 0;
        }

        // call function
        cobj->setScaleY(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setScaleY", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setScaleX(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setScaleX'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setScaleX'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setScaleX");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setScaleX'", NULL);
            return 0;
        }

        // call function
        cobj->setScaleX(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setScaleX", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_scheduleUpdateWithPriority(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_scheduleUpdateWithPriority'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_scheduleUpdateWithPriority'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:scheduleUpdateWithPriority");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_scheduleUpdateWithPriority'", NULL);
            return 0;
        }

        // call function
        cobj->scheduleUpdateWithPriority(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:scheduleUpdateWithPriority", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_unregisterScriptHandler(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_unregisterScriptHandler'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_unregisterScriptHandler'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->unregisterScriptHandler();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:unregisterScriptHandler", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getTag(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getTag'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getTag'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        int ret = cobj->getTag();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getTag", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_onExit(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_onExit'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_onExit'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->onExit();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:onExit", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_removeChild(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_removeChild'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_removeChild'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // try call function
    do {
        if (argc == 2) {
            // arguments declaration
            CCNode* arg0;
            bool arg1;

            // convert lua value to desired arguments
            ok &= luaval_to_object<CCNode>(tolua_S, 2, "CCNode", &arg0);
            ok &= luaval_to_boolean(tolua_S, 3, &arg1, "CCNode:removeChild");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->removeChild(arg0, arg1);
            return 0;
        }
    } while(0);
    ok = true;

    // try call function
    do {
        if (argc == 1) {
            // arguments declaration
            CCNode* arg0;

            // convert lua value to desired arguments
            ok &= luaval_to_object<CCNode>(tolua_S, 2, "CCNode", &arg0);

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->removeChild(arg0);
            return 0;
        }
    } while(0);
    ok = true;

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "CCNode:removeChild",argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_convertToWorldSpace(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_convertToWorldSpace'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_convertToWorldSpace'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCPoint arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_point(tolua_S, 2, &arg0, "CCNode:convertToWorldSpace");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_convertToWorldSpace'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCPoint ret = cobj->convertToWorldSpace(arg0);
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:convertToWorldSpace", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setSkewX(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setSkewX'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setSkewX'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setSkewX");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setSkewX'", NULL);
            return 0;
        }

        // call function
        cobj->setSkewX(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setSkewX", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setSkewY(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setSkewY'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setSkewY'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setSkewY");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setSkewY'", NULL);
            return 0;
        }

        // call function
        cobj->setSkewY(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setSkewY", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_onEnterTransitionDidFinish(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_onEnterTransitionDidFinish'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_onEnterTransitionDidFinish'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->onEnterTransitionDidFinish();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:onEnterTransitionDidFinish", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_convertTouchToNodeSpace(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_convertTouchToNodeSpace'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_convertTouchToNodeSpace'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCTouch* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCTouch>(tolua_S, 2, "CCTouch", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_convertTouchToNodeSpace'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCPoint ret = cobj->convertTouchToNodeSpace(arg0);
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:convertTouchToNodeSpace", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_removeAllChildren(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_removeAllChildren'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_removeAllChildren'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->removeAllChildren();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:removeAllChildren", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getRotationX(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getRotationX'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getRotationX'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getRotationX();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getRotationX", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getRotationY(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getRotationY'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getRotationY'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getRotationY();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getRotationY", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_unscheduleUpdate(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_unscheduleUpdate'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_unscheduleUpdate'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->unscheduleUpdate();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:unscheduleUpdate", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_setParent(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setParent'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setParent'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCNode* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCNode>(tolua_S, 2, "CCNode", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setParent'", NULL);
            return 0;
        }

        // call function
        cobj->setParent(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setParent", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_nodeToParentTransform(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_nodeToParentTransform'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_nodeToParentTransform'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCAffineTransform ret = cobj->nodeToParentTransform();
        affinetransform_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:nodeToParentTransform", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_unscheduleAllSelectors(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_unscheduleAllSelectors'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_unscheduleAllSelectors'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->unscheduleAllSelectors();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:unscheduleAllSelectors", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_removeAllChildrenWithCleanup(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_removeAllChildrenWithCleanup'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_removeAllChildrenWithCleanup'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        bool arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_boolean(tolua_S, 2, &arg0, "CCNode:removeAllChildrenWithCleanup");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_removeAllChildrenWithCleanup'", NULL);
            return 0;
        }

        // call function
        cobj->removeAllChildrenWithCleanup(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:removeAllChildrenWithCleanup", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_getGrid(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getGrid'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getGrid'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCGridBase* ret = cobj->getGrid();
        object_to_luaval<cocos2d::CCGridBase>(tolua_S, "CCGridBase", (cocos2d::CCGridBase*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getGrid", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_numberOfRunningActions(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_numberOfRunningActions'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_numberOfRunningActions'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        unsigned int ret = cobj->numberOfRunningActions();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:numberOfRunningActions", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_removeFromParentAndCleanup(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_removeFromParentAndCleanup'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_removeFromParentAndCleanup'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        bool arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_boolean(tolua_S, 2, &arg0, "CCNode:removeFromParentAndCleanup");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_removeFromParentAndCleanup'", NULL);
            return 0;
        }

        // call function
        cobj->removeFromParentAndCleanup(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:removeFromParentAndCleanup", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setPosition(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setPosition'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setPosition'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // try call function
    do {
        if (argc == 2) {
            // arguments declaration
            double arg0;
            double arg1;

            // convert lua value to desired arguments
            ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setPosition");
            ok &= luaval_to_number(tolua_S, 3, &arg1, "CCNode:setPosition");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->setPosition(arg0, arg1);
            return 0;
        }
    } while(0);
    ok = true;

    // try call function
    do {
        if (argc == 1) {
            // arguments declaration
            CCPoint arg0;

            // convert lua value to desired arguments
            ok &= luaval_to_point(tolua_S, 2, &arg0, "CCNode:setPosition");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->setPosition(arg0);
            return 0;
        }
    } while(0);
    ok = true;

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "CCNode:setPosition",argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_stopActionByTag(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_stopActionByTag'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_stopActionByTag'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:stopActionByTag");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_stopActionByTag'", NULL);
            return 0;
        }

        // call function
        cobj->stopActionByTag(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:stopActionByTag", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_reorderChild(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_reorderChild'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_reorderChild'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 2) {
        // arguments declaration
        CCNode* arg0;
        int arg1;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCNode>(tolua_S, 2, "CCNode", &arg0);
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "CCNode:reorderChild");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_reorderChild'", NULL);
            return 0;
        }

        // call function
        cobj->reorderChild(arg0, arg1);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:reorderChild", argc, 2);
    return 0;
}

int lua_cocos2dx_CCNode_setGLServerState(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setGLServerState'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setGLServerState'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        ccGLServerState arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:setGLServerState");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setGLServerState'", NULL);
            return 0;
        }

        // call function
        cobj->setGLServerState(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setGLServerState", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setPositionY(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setPositionY'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setPositionY'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setPositionY");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setPositionY'", NULL);
            return 0;
        }

        // call function
        cobj->setPositionY(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setPositionY", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setPositionX(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setPositionX'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setPositionX'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setPositionX");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setPositionX'", NULL);
            return 0;
        }

        // call function
        cobj->setPositionX(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setPositionX", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_getAnchorPoint(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getAnchorPoint'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getAnchorPoint'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        const cocos2d::CCPoint& ret = cobj->getAnchorPoint();
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getAnchorPoint", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_updateTransform(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_updateTransform'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_updateTransform'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->updateTransform();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:updateTransform", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_isVisible(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_isVisible'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_isVisible'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        bool ret = cobj->isVisible();
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:isVisible", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getChildrenCount(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getChildrenCount'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getChildrenCount'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        unsigned int ret = cobj->getChildrenCount();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getChildrenCount", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_setAnchorPoint(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setAnchorPoint'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setAnchorPoint'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCPoint arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_point(tolua_S, 2, &arg0, "CCNode:setAnchorPoint");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setAnchorPoint'", NULL);
            return 0;
        }

        // call function
        cobj->setAnchorPoint(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setAnchorPoint", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_onEnter(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_onEnter'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_onEnter'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->onEnter();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:onEnter", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_convertToNodeSpaceAR(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_convertToNodeSpaceAR'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_convertToNodeSpaceAR'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCPoint arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_point(tolua_S, 2, &arg0, "CCNode:convertToNodeSpaceAR");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_convertToNodeSpaceAR'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCPoint ret = cobj->convertToNodeSpaceAR(arg0);
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:convertToNodeSpaceAR", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_addComponent(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_addComponent'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_addComponent'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCComponent* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCComponent>(tolua_S, 2, "CCComponent", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_addComponent'", NULL);
            return 0;
        }

        // call function
        bool ret = cobj->addComponent(arg0);
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:addComponent", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_runAction(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_runAction'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_runAction'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCAction* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCAction>(tolua_S, 2, "CCAction", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_runAction'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCAction* ret = cobj->runAction(arg0);
        object_to_luaval<cocos2d::CCAction>(tolua_S, "CCAction", (cocos2d::CCAction*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:runAction", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setShaderProgram(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setShaderProgram'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setShaderProgram'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCGLProgram* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCGLProgram>(tolua_S, 2, "CCGLProgram", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setShaderProgram'", NULL);
            return 0;
        }

        // call function
        cobj->setShaderProgram(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setShaderProgram", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_scheduleUpdateWithPriorityLua(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_scheduleUpdateWithPriorityLua'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_scheduleUpdateWithPriorityLua'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 2) {
        // arguments declaration
        int arg0;
        int arg1;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:scheduleUpdateWithPriorityLua");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "CCNode:scheduleUpdateWithPriorityLua");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_scheduleUpdateWithPriorityLua'", NULL);
            return 0;
        }

        // call function
        cobj->scheduleUpdateWithPriorityLua(arg0, arg1);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:scheduleUpdateWithPriorityLua", argc, 2);
    return 0;
}

int lua_cocos2dx_CCNode_getRotation(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getRotation'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getRotation'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getRotation();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getRotation", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_resumeSchedulerAndActions(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_resumeSchedulerAndActions'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_resumeSchedulerAndActions'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->resumeSchedulerAndActions();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:resumeSchedulerAndActions", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getZOrder(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getZOrder'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getZOrder'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        int ret = cobj->getZOrder();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getZOrder", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getAnchorPointInPoints(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getAnchorPointInPoints'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getAnchorPointInPoints'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        const cocos2d::CCPoint& ret = cobj->getAnchorPointInPoints();
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getAnchorPointInPoints", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_visit(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_visit'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_visit'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->visit();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:visit", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_transform(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_transform'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_transform'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->transform();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:transform", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_setVertexZ(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setVertexZ'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setVertexZ'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setVertexZ");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setVertexZ'", NULL);
            return 0;
        }

        // call function
        cobj->setVertexZ(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setVertexZ", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setScheduler(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setScheduler'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setScheduler'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCScheduler* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCScheduler>(tolua_S, 2, "CCScheduler", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setScheduler'", NULL);
            return 0;
        }

        // call function
        cobj->setScheduler(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setScheduler", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_stopAllActions(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_stopAllActions'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_stopAllActions'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->stopAllActions();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:stopAllActions", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getSkewX(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getSkewX'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getSkewX'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getSkewX();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getSkewX", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getSkewY(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getSkewY'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getSkewY'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getSkewY();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getSkewY", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_ignoreAnchorPointForPosition(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_ignoreAnchorPointForPosition'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_ignoreAnchorPointForPosition'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        bool arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_boolean(tolua_S, 2, &arg0, "CCNode:ignoreAnchorPointForPosition");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_ignoreAnchorPointForPosition'", NULL);
            return 0;
        }

        // call function
        cobj->ignoreAnchorPointForPosition(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:ignoreAnchorPointForPosition", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_getActionByTag(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getActionByTag'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getActionByTag'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:getActionByTag");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_getActionByTag'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCAction* ret = cobj->getActionByTag(arg0);
        object_to_luaval<cocos2d::CCAction>(tolua_S, "CCAction", (cocos2d::CCAction*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getActionByTag", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setRotationX(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setRotationX'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setRotationX'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setRotationX");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setRotationX'", NULL);
            return 0;
        }

        // call function
        cobj->setRotationX(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setRotationX", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setRotationY(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setRotationY'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setRotationY'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setRotationY");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setRotationY'", NULL);
            return 0;
        }

        // call function
        cobj->setRotationY(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setRotationY", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setAdditionalTransform(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setAdditionalTransform'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setAdditionalTransform'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCAffineTransform arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_affinetransform(tolua_S, 2, &arg0, "CCNode:setAdditionalTransform");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setAdditionalTransform'", NULL);
            return 0;
        }

        // call function
        cobj->setAdditionalTransform(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setAdditionalTransform", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_getScheduler(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getScheduler'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getScheduler'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCScheduler* ret = cobj->getScheduler();
        object_to_luaval<cocos2d::CCScheduler>(tolua_S, "CCScheduler", (cocos2d::CCScheduler*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getScheduler", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getOrderOfArrival(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getOrderOfArrival'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getOrderOfArrival'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        unsigned int ret = cobj->getOrderOfArrival();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getOrderOfArrival", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_boundingBox(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_boundingBox'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_boundingBox'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCRect ret = cobj->boundingBox();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:boundingBox", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_setContentSize(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setContentSize'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setContentSize'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCSize arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_size(tolua_S, 2, &arg0, "CCNode:setContentSize");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setContentSize'", NULL);
            return 0;
        }

        // call function
        cobj->setContentSize(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setContentSize", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setActionManager(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setActionManager'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setActionManager'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCActionManager* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCActionManager>(tolua_S, 2, "CCActionManager", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setActionManager'", NULL);
            return 0;
        }

        // call function
        cobj->setActionManager(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setActionManager", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_getPosition(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getPosition'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getPosition'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        const cocos2d::CCPoint& ret = cobj->getPosition();
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getPosition", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_isRunning(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_isRunning'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_isRunning'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        bool ret = cobj->isRunning();
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:isRunning", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getParent(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getParent'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getParent'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCNode* ret = cobj->getParent();
        object_to_luaval<cocos2d::CCNode>(tolua_S, "CCNode", (cocos2d::CCNode*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getParent", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getPositionY(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getPositionY'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getPositionY'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getPositionY();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getPositionY", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getPositionX(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getPositionX'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getPositionX'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getPositionX();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getPositionX", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_removeChildByTag(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_removeChildByTag'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_removeChildByTag'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // try call function
    do {
        if (argc == 2) {
            // arguments declaration
            int arg0;
            bool arg1;

            // convert lua value to desired arguments
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:removeChildByTag");
            ok &= luaval_to_boolean(tolua_S, 3, &arg1, "CCNode:removeChildByTag");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->removeChildByTag(arg0, arg1);
            return 0;
        }
    } while(0);
    ok = true;

    // try call function
    do {
        if (argc == 1) {
            // arguments declaration
            int arg0;

            // convert lua value to desired arguments
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:removeChildByTag");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->removeChildByTag(arg0);
            return 0;
        }
    } while(0);
    ok = true;

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "CCNode:removeChildByTag",argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setVisible(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setVisible'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setVisible'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        bool arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_boolean(tolua_S, 2, &arg0, "CCNode:setVisible");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setVisible'", NULL);
            return 0;
        }

        // call function
        cobj->setVisible(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setVisible", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_pauseSchedulerAndActions(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_pauseSchedulerAndActions'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_pauseSchedulerAndActions'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->pauseSchedulerAndActions();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:pauseSchedulerAndActions", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getVertexZ(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getVertexZ'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getVertexZ'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getVertexZ();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getVertexZ", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode__setZOrder(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode__setZOrder'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode__setZOrder'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:_setZOrder");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode__setZOrder'", NULL);
            return 0;
        }

        // call function
        cobj->_setZOrder(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:_setZOrder", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setScale(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setScale'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setScale'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // try call function
    do {
        if (argc == 2) {
            // arguments declaration
            double arg0;
            double arg1;

            // convert lua value to desired arguments
            ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setScale");
            ok &= luaval_to_number(tolua_S, 3, &arg1, "CCNode:setScale");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->setScale(arg0, arg1);
            return 0;
        }
    } while(0);
    ok = true;

    // try call function
    do {
        if (argc == 1) {
            // arguments declaration
            double arg0;

            // convert lua value to desired arguments
            ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:setScale");

            // if conversion is not ok, print error and return
            if(!ok) { break; }

            // call function
            cobj->setScale(arg0);
            return 0;
        }
    } while(0);
    ok = true;

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "CCNode:setScale",argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_getChildByTag(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getChildByTag'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getChildByTag'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:getChildByTag");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_getChildByTag'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCNode* ret = cobj->getChildByTag(arg0);
        object_to_luaval<cocos2d::CCNode>(tolua_S, "CCNode", (cocos2d::CCNode*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getChildByTag", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_setOrderOfArrival(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setOrderOfArrival'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setOrderOfArrival'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        unsigned int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_uint32(tolua_S, 2, &arg0, "CCNode:setOrderOfArrival");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setOrderOfArrival'", NULL);
            return 0;
        }

        // call function
        cobj->setOrderOfArrival(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setOrderOfArrival", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_getScaleY(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getScaleY'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getScaleY'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getScaleY();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getScaleY", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getScaleX(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getScaleX'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getScaleX'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getScaleX();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getScaleX", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_cleanup(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_cleanup'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_cleanup'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->cleanup();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:cleanup", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getContentSize(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getContentSize'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getContentSize'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        const cocos2d::CCSize& ret = cobj->getContentSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getContentSize", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_setGrid(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setGrid'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setGrid'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCGridBase* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCGridBase>(tolua_S, 2, "CCGridBase", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setGrid'", NULL);
            return 0;
        }

        // call function
        cobj->setGrid(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setGrid", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_draw(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_draw'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_draw'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->draw();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:draw", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_transformAncestors(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_transformAncestors'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_transformAncestors'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->transformAncestors();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:transformAncestors", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_setUserObject(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setUserObject'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setUserObject'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCObject* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCObject>(tolua_S, 2, "CCObject", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setUserObject'", NULL);
            return 0;
        }

        // call function
        cobj->setUserObject(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setUserObject", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_registerScriptHandler(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_registerScriptHandler'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_registerScriptHandler'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:registerScriptHandler");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_registerScriptHandler'", NULL);
            return 0;
        }

        // call function
        cobj->registerScriptHandler(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:registerScriptHandler", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_removeFromParent(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_removeFromParent'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_removeFromParent'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->removeFromParent();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:removeFromParent", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_convertTouchToNodeSpaceAR(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_convertTouchToNodeSpaceAR'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_convertTouchToNodeSpaceAR'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCTouch* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCTouch>(tolua_S, 2, "CCTouch", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_convertTouchToNodeSpaceAR'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCPoint ret = cobj->convertTouchToNodeSpaceAR(arg0);
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:convertTouchToNodeSpaceAR", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_CCNode(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // create object, if object is a CCObject subclass, autorelease it
        // if not, register gc in lua
        cobj = new cocos2d::CCNode();
        cobj->autorelease();
        int ID = (int)cobj->m_uID ;
        int* luaID = &cobj->m_nLuaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj, "CCNode");
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:CCNode", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_update(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_update'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_update'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        double arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_number(tolua_S, 2, &arg0, "CCNode:update");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_update'", NULL);
            return 0;
        }

        // call function
        cobj->update(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:update", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_sortAllChildren(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_sortAllChildren'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_sortAllChildren'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->sortAllChildren();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:sortAllChildren", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_convertToNodeSpace(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_convertToNodeSpace'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_convertToNodeSpace'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCPoint arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_point(tolua_S, 2, &arg0, "CCNode:convertToNodeSpace");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_convertToNodeSpace'", NULL);
            return 0;
        }

        // call function
        cocos2d::CCPoint ret = cobj->convertToNodeSpace(arg0);
        point_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:convertToNodeSpace", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_onExitTransitionDidStart(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_onExitTransitionDidStart'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_onExitTransitionDidStart'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->onExitTransitionDidStart();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:onExitTransitionDidStart", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getScale(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getScale'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getScale'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        double ret = cobj->getScale();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getScale", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_worldToNodeTransform(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_worldToNodeTransform'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_worldToNodeTransform'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCAffineTransform ret = cobj->worldToNodeTransform();
        affinetransform_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:worldToNodeTransform", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_parentToNodeTransform(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_parentToNodeTransform'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_parentToNodeTransform'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCAffineTransform ret = cobj->parentToNodeTransform();
        affinetransform_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:parentToNodeTransform", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getCamera(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getCamera'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getCamera'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCCamera* ret = cobj->getCamera();
        object_to_luaval<cocos2d::CCCamera>(tolua_S, "CCCamera", (cocos2d::CCCamera*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getCamera", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_setTag(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_setTag'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_setTag'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        int arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCNode:setTag");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_setTag'", NULL);
            return 0;
        }

        // call function
        cobj->setTag(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:setTag", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_scheduleUpdate(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_scheduleUpdate'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_scheduleUpdate'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cobj->scheduleUpdate();
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:scheduleUpdate", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_getGLServerState(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getGLServerState'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getGLServerState'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        int ret = (int)cobj->getGLServerState();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getGLServerState", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNode_stopAction(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_stopAction'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_stopAction'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        CCAction* arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_object<CCAction>(tolua_S, 2, "CCAction", &arg0);

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNode_stopAction'", NULL);
            return 0;
        }

        // call function
        cobj->stopAction(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:stopAction", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNode_getActionManager(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNode* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNode", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNode_getActionManager'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNode*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNode_getActionManager'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCActionManager* ret = cobj->getActionManager();
        object_to_luaval<cocos2d::CCActionManager>(tolua_S, "CCActionManager", (cocos2d::CCActionManager*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNode:getActionManager", argc, 0);
    return 0;
}

int lua_register_cocos2dx_CCNode(lua_State* tolua_S) {
    tolua_usertype(tolua_S, "CCNode");
    tolua_cclass(tolua_S, "CCNode", "CCNode", "CCObject", NULL);

    // register module
    tolua_beginmodule(tolua_S, "CCNode");
        tolua_function(tolua_S, "addChild", lua_cocos2dx_CCNode_addChild);
        tolua_function(tolua_S, "removeComponent", lua_cocos2dx_CCNode_removeComponent);
        tolua_function(tolua_S, "nodeToWorldTransform", lua_cocos2dx_CCNode_nodeToWorldTransform);
        tolua_function(tolua_S, "removeAllComponents", lua_cocos2dx_CCNode_removeAllComponents);
        tolua_function(tolua_S, "getShaderProgram", lua_cocos2dx_CCNode_getShaderProgram);
        tolua_function(tolua_S, "getUserObject", lua_cocos2dx_CCNode_getUserObject);
        tolua_function(tolua_S, "getChildren", lua_cocos2dx_CCNode_getChildren);
        tolua_function(tolua_S, "getScriptHandler", lua_cocos2dx_CCNode_getScriptHandler);
        tolua_function(tolua_S, "convertToWorldSpaceAR", lua_cocos2dx_CCNode_convertToWorldSpaceAR);
        tolua_function(tolua_S, "isIgnoreAnchorPointForPosition", lua_cocos2dx_CCNode_isIgnoreAnchorPointForPosition);
        tolua_function(tolua_S, "init", lua_cocos2dx_CCNode_init);
        tolua_function(tolua_S, "setRotation", lua_cocos2dx_CCNode_setRotation);
        tolua_function(tolua_S, "setZOrder", lua_cocos2dx_CCNode_setZOrder);
        tolua_function(tolua_S, "setScaleY", lua_cocos2dx_CCNode_setScaleY);
        tolua_function(tolua_S, "setScaleX", lua_cocos2dx_CCNode_setScaleX);
        tolua_function(tolua_S, "scheduleUpdateWithPriority", lua_cocos2dx_CCNode_scheduleUpdateWithPriority);
        tolua_function(tolua_S, "unregisterScriptHandler", lua_cocos2dx_CCNode_unregisterScriptHandler);
        tolua_function(tolua_S, "getTag", lua_cocos2dx_CCNode_getTag);
        tolua_function(tolua_S, "onExit", lua_cocos2dx_CCNode_onExit);
        tolua_function(tolua_S, "removeChild", lua_cocos2dx_CCNode_removeChild);
        tolua_function(tolua_S, "convertToWorldSpace", lua_cocos2dx_CCNode_convertToWorldSpace);
        tolua_function(tolua_S, "setSkewX", lua_cocos2dx_CCNode_setSkewX);
        tolua_function(tolua_S, "setSkewY", lua_cocos2dx_CCNode_setSkewY);
        tolua_function(tolua_S, "onEnterTransitionDidFinish", lua_cocos2dx_CCNode_onEnterTransitionDidFinish);
        tolua_function(tolua_S, "convertTouchToNodeSpace", lua_cocos2dx_CCNode_convertTouchToNodeSpace);
        tolua_function(tolua_S, "removeAllChildren", lua_cocos2dx_CCNode_removeAllChildren);
        tolua_function(tolua_S, "getRotationX", lua_cocos2dx_CCNode_getRotationX);
        tolua_function(tolua_S, "getRotationY", lua_cocos2dx_CCNode_getRotationY);
        tolua_function(tolua_S, "unscheduleUpdate", lua_cocos2dx_CCNode_unscheduleUpdate);
        tolua_function(tolua_S, "setParent", lua_cocos2dx_CCNode_setParent);
        tolua_function(tolua_S, "nodeToParentTransform", lua_cocos2dx_CCNode_nodeToParentTransform);
        tolua_function(tolua_S, "unscheduleAllSelectors", lua_cocos2dx_CCNode_unscheduleAllSelectors);
        tolua_function(tolua_S, "removeAllChildrenWithCleanup", lua_cocos2dx_CCNode_removeAllChildrenWithCleanup);
        tolua_function(tolua_S, "getGrid", lua_cocos2dx_CCNode_getGrid);
        tolua_function(tolua_S, "numberOfRunningActions", lua_cocos2dx_CCNode_numberOfRunningActions);
        tolua_function(tolua_S, "removeFromParentAndCleanup", lua_cocos2dx_CCNode_removeFromParentAndCleanup);
        tolua_function(tolua_S, "setPosition", lua_cocos2dx_CCNode_setPosition);
        tolua_function(tolua_S, "stopActionByTag", lua_cocos2dx_CCNode_stopActionByTag);
        tolua_function(tolua_S, "reorderChild", lua_cocos2dx_CCNode_reorderChild);
        tolua_function(tolua_S, "setGLServerState", lua_cocos2dx_CCNode_setGLServerState);
        tolua_function(tolua_S, "setPositionY", lua_cocos2dx_CCNode_setPositionY);
        tolua_function(tolua_S, "setPositionX", lua_cocos2dx_CCNode_setPositionX);
        tolua_function(tolua_S, "getAnchorPoint", lua_cocos2dx_CCNode_getAnchorPoint);
        tolua_function(tolua_S, "updateTransform", lua_cocos2dx_CCNode_updateTransform);
        tolua_function(tolua_S, "isVisible", lua_cocos2dx_CCNode_isVisible);
        tolua_function(tolua_S, "getChildrenCount", lua_cocos2dx_CCNode_getChildrenCount);
        tolua_function(tolua_S, "setAnchorPoint", lua_cocos2dx_CCNode_setAnchorPoint);
        tolua_function(tolua_S, "onEnter", lua_cocos2dx_CCNode_onEnter);
        tolua_function(tolua_S, "convertToNodeSpaceAR", lua_cocos2dx_CCNode_convertToNodeSpaceAR);
        tolua_function(tolua_S, "addComponent", lua_cocos2dx_CCNode_addComponent);
        tolua_function(tolua_S, "runAction", lua_cocos2dx_CCNode_runAction);
        tolua_function(tolua_S, "setShaderProgram", lua_cocos2dx_CCNode_setShaderProgram);
        tolua_function(tolua_S, "scheduleUpdateWithPriorityLua", lua_cocos2dx_CCNode_scheduleUpdateWithPriorityLua);
        tolua_function(tolua_S, "getRotation", lua_cocos2dx_CCNode_getRotation);
        tolua_function(tolua_S, "resumeSchedulerAndActions", lua_cocos2dx_CCNode_resumeSchedulerAndActions);
        tolua_function(tolua_S, "getZOrder", lua_cocos2dx_CCNode_getZOrder);
        tolua_function(tolua_S, "getAnchorPointInPoints", lua_cocos2dx_CCNode_getAnchorPointInPoints);
        tolua_function(tolua_S, "visit", lua_cocos2dx_CCNode_visit);
        tolua_function(tolua_S, "transform", lua_cocos2dx_CCNode_transform);
        tolua_function(tolua_S, "setVertexZ", lua_cocos2dx_CCNode_setVertexZ);
        tolua_function(tolua_S, "setScheduler", lua_cocos2dx_CCNode_setScheduler);
        tolua_function(tolua_S, "stopAllActions", lua_cocos2dx_CCNode_stopAllActions);
        tolua_function(tolua_S, "getSkewX", lua_cocos2dx_CCNode_getSkewX);
        tolua_function(tolua_S, "getSkewY", lua_cocos2dx_CCNode_getSkewY);
        tolua_function(tolua_S, "ignoreAnchorPointForPosition", lua_cocos2dx_CCNode_ignoreAnchorPointForPosition);
        tolua_function(tolua_S, "getActionByTag", lua_cocos2dx_CCNode_getActionByTag);
        tolua_function(tolua_S, "setRotationX", lua_cocos2dx_CCNode_setRotationX);
        tolua_function(tolua_S, "setRotationY", lua_cocos2dx_CCNode_setRotationY);
        tolua_function(tolua_S, "setAdditionalTransform", lua_cocos2dx_CCNode_setAdditionalTransform);
        tolua_function(tolua_S, "getScheduler", lua_cocos2dx_CCNode_getScheduler);
        tolua_function(tolua_S, "getOrderOfArrival", lua_cocos2dx_CCNode_getOrderOfArrival);
        tolua_function(tolua_S, "boundingBox", lua_cocos2dx_CCNode_boundingBox);
        tolua_function(tolua_S, "setContentSize", lua_cocos2dx_CCNode_setContentSize);
        tolua_function(tolua_S, "setActionManager", lua_cocos2dx_CCNode_setActionManager);
        tolua_function(tolua_S, "getPosition", lua_cocos2dx_CCNode_getPosition);
        tolua_function(tolua_S, "isRunning", lua_cocos2dx_CCNode_isRunning);
        tolua_function(tolua_S, "getParent", lua_cocos2dx_CCNode_getParent);
        tolua_function(tolua_S, "getPositionY", lua_cocos2dx_CCNode_getPositionY);
        tolua_function(tolua_S, "getPositionX", lua_cocos2dx_CCNode_getPositionX);
        tolua_function(tolua_S, "removeChildByTag", lua_cocos2dx_CCNode_removeChildByTag);
        tolua_function(tolua_S, "setVisible", lua_cocos2dx_CCNode_setVisible);
        tolua_function(tolua_S, "pauseSchedulerAndActions", lua_cocos2dx_CCNode_pauseSchedulerAndActions);
        tolua_function(tolua_S, "getVertexZ", lua_cocos2dx_CCNode_getVertexZ);
        tolua_function(tolua_S, "_setZOrder", lua_cocos2dx_CCNode__setZOrder);
        tolua_function(tolua_S, "setScale", lua_cocos2dx_CCNode_setScale);
        tolua_function(tolua_S, "getChildByTag", lua_cocos2dx_CCNode_getChildByTag);
        tolua_function(tolua_S, "setOrderOfArrival", lua_cocos2dx_CCNode_setOrderOfArrival);
        tolua_function(tolua_S, "getScaleY", lua_cocos2dx_CCNode_getScaleY);
        tolua_function(tolua_S, "getScaleX", lua_cocos2dx_CCNode_getScaleX);
        tolua_function(tolua_S, "cleanup", lua_cocos2dx_CCNode_cleanup);
        tolua_function(tolua_S, "getContentSize", lua_cocos2dx_CCNode_getContentSize);
        tolua_function(tolua_S, "setGrid", lua_cocos2dx_CCNode_setGrid);
        tolua_function(tolua_S, "draw", lua_cocos2dx_CCNode_draw);
        tolua_function(tolua_S, "transformAncestors", lua_cocos2dx_CCNode_transformAncestors);
        tolua_function(tolua_S, "setUserObject", lua_cocos2dx_CCNode_setUserObject);
        tolua_function(tolua_S, "registerScriptHandler", lua_cocos2dx_CCNode_registerScriptHandler);
        tolua_function(tolua_S, "removeFromParent", lua_cocos2dx_CCNode_removeFromParent);
        tolua_function(tolua_S, "convertTouchToNodeSpaceAR", lua_cocos2dx_CCNode_convertTouchToNodeSpaceAR);
        tolua_function(tolua_S, "new", lua_cocos2dx_CCNode_CCNode);
        tolua_function(tolua_S, "update", lua_cocos2dx_CCNode_update);
        tolua_function(tolua_S, "sortAllChildren", lua_cocos2dx_CCNode_sortAllChildren);
        tolua_function(tolua_S, "convertToNodeSpace", lua_cocos2dx_CCNode_convertToNodeSpace);
        tolua_function(tolua_S, "onExitTransitionDidStart", lua_cocos2dx_CCNode_onExitTransitionDidStart);
        tolua_function(tolua_S, "getScale", lua_cocos2dx_CCNode_getScale);
        tolua_function(tolua_S, "worldToNodeTransform", lua_cocos2dx_CCNode_worldToNodeTransform);
        tolua_function(tolua_S, "parentToNodeTransform", lua_cocos2dx_CCNode_parentToNodeTransform);
        tolua_function(tolua_S, "getCamera", lua_cocos2dx_CCNode_getCamera);
        tolua_function(tolua_S, "setTag", lua_cocos2dx_CCNode_setTag);
        tolua_function(tolua_S, "scheduleUpdate", lua_cocos2dx_CCNode_scheduleUpdate);
        tolua_function(tolua_S, "getGLServerState", lua_cocos2dx_CCNode_getGLServerState);
        tolua_function(tolua_S, "stopAction", lua_cocos2dx_CCNode_stopAction);
        tolua_function(tolua_S, "getActionManager", lua_cocos2dx_CCNode_getActionManager);
        tolua_function(tolua_S, "create", lua_cocos2dx_CCNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::CCNode).name();
    g_luaType[typeName] = "CCNode";
    g_typeCast["CCNode"] = "CCNode";
    return 1;
}

int lua_cocos2dx_CCNodeRGBA_create(lua_State* tolua_S) {
    // variables
    int argc = 0;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S, 1,"CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_create'.", &tolua_err);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        cocos2d::CCNodeRGBA* ret = cocos2d::CCNodeRGBA::create();
        object_to_luaval<cocos2d::CCNodeRGBA>(tolua_S, "CCNodeRGBA", (cocos2d::CCNodeRGBA*)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:create", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_updateDisplayedColor(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_updateDisplayedColor'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_updateDisplayedColor'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        ccColor3B arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "CCNodeRGBA:updateDisplayedColor");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNodeRGBA_updateDisplayedColor'", NULL);
            return 0;
        }

        // call function
        cobj->updateDisplayedColor(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:updateDisplayedColor", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_setColor(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_setColor'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_setColor'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        ccColor3B arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_color3b(tolua_S, 2, &arg0, "CCNodeRGBA:setColor");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNodeRGBA_setColor'", NULL);
            return 0;
        }

        // call function
        cobj->setColor(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:setColor", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_isCascadeOpacityEnabled(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_isCascadeOpacityEnabled'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_isCascadeOpacityEnabled'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        bool ret = cobj->isCascadeOpacityEnabled();
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:isCascadeOpacityEnabled", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_getColor(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_getColor'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_getColor'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        const cocos2d::ccColor3B& ret = cobj->getColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:getColor", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_getDisplayedOpacity(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_getDisplayedOpacity'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_getDisplayedOpacity'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        uint16_t ret = cobj->getDisplayedOpacity();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:getDisplayedOpacity", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_setCascadeColorEnabled(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_setCascadeColorEnabled'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_setCascadeColorEnabled'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        bool arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_boolean(tolua_S, 2, &arg0, "CCNodeRGBA:setCascadeColorEnabled");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNodeRGBA_setCascadeColorEnabled'", NULL);
            return 0;
        }

        // call function
        cobj->setCascadeColorEnabled(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:setCascadeColorEnabled", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_setOpacity(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_setOpacity'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_setOpacity'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        uint16_t arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_uint16(tolua_S, 2, &arg0, "CCNodeRGBA:setOpacity");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNodeRGBA_setOpacity'", NULL);
            return 0;
        }

        // call function
        cobj->setOpacity(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:setOpacity", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_setCascadeOpacityEnabled(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_setCascadeOpacityEnabled'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_setCascadeOpacityEnabled'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        bool arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_boolean(tolua_S, 2, &arg0, "CCNodeRGBA:setCascadeOpacityEnabled");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNodeRGBA_setCascadeOpacityEnabled'", NULL);
            return 0;
        }

        // call function
        cobj->setCascadeOpacityEnabled(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:setCascadeOpacityEnabled", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_updateDisplayedOpacity(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_updateDisplayedOpacity'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_updateDisplayedOpacity'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        uint16_t arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_uint16(tolua_S, 2, &arg0, "CCNodeRGBA:updateDisplayedOpacity");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNodeRGBA_updateDisplayedOpacity'", NULL);
            return 0;
        }

        // call function
        cobj->updateDisplayedOpacity(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:updateDisplayedOpacity", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_init(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_init'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_init'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:init", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_CCNodeRGBA(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // create object, if object is a CCObject subclass, autorelease it
        // if not, register gc in lua
        cobj = new cocos2d::CCNodeRGBA();
        cobj->autorelease();
        int ID = (int)cobj->m_uID ;
        int* luaID = &cobj->m_nLuaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj, "CCNodeRGBA");
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:CCNodeRGBA", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_setOpacityModifyRGB(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_setOpacityModifyRGB'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_setOpacityModifyRGB'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 1) {
        // arguments declaration
        bool arg0;

        // convert lua value to desired arguments
        ok &= luaval_to_boolean(tolua_S, 2, &arg0, "CCNodeRGBA:setOpacityModifyRGB");

        // if conversion is not ok, print error and return
        if(!ok) {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_CCNodeRGBA_setOpacityModifyRGB'", NULL);
            return 0;
        }

        // call function
        cobj->setOpacityModifyRGB(arg0);
        return 0;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:setOpacityModifyRGB", argc, 1);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_getOpacity(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_getOpacity'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_getOpacity'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        uint16_t ret = cobj->getOpacity();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:getOpacity", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_isOpacityModifyRGB(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_isOpacityModifyRGB'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_isOpacityModifyRGB'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        bool ret = cobj->isOpacityModifyRGB();
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:isOpacityModifyRGB", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_isCascadeColorEnabled(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_isCascadeColorEnabled'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_isCascadeColorEnabled'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        bool ret = cobj->isCascadeColorEnabled();
        tolua_pushboolean(tolua_S, (bool)ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:isCascadeColorEnabled", argc, 0);
    return 0;
}

int lua_cocos2dx_CCNodeRGBA_getDisplayedColor(lua_State* tolua_S) {
    // variables
    int argc = 0;
    cocos2d::CCNodeRGBA* cobj = NULL;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

    // if not constructor, validate the top is our desired object type
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S, 1, "CCNodeRGBA", 0, &tolua_err)) {
        tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_CCNodeRGBA_getDisplayedColor'.", &tolua_err);
        return 0;
    }
#endif
    cobj = (cocos2d::CCNodeRGBA*)tolua_tousertype(tolua_S, 1, 0);
#if COCOS2D_DEBUG >= 1
    if (!cobj) {
        tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_CCNodeRGBA_getDisplayedColor'", NULL);
        return 0;
    }
#endif

    // get argument count
    argc = lua_gettop(tolua_S) - 1;

    // if argument count matched, call
    if (argc == 0) {

        // call function
        const cocos2d::ccColor3B& ret = cobj->getDisplayedColor();
        color3b_to_luaval(tolua_S, ret);
        return 1;
    }

    // if to here, means argument count is not correct
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCNodeRGBA:getDisplayedColor", argc, 0);
    return 0;
}

int lua_register_cocos2dx_CCNodeRGBA(lua_State* tolua_S) {
    tolua_usertype(tolua_S, "CCNodeRGBA");
    tolua_cclass(tolua_S, "CCNodeRGBA", "CCNodeRGBA", "CCNode", NULL);

    // register module
    tolua_beginmodule(tolua_S, "CCNodeRGBA");
        tolua_function(tolua_S, "updateDisplayedColor", lua_cocos2dx_CCNodeRGBA_updateDisplayedColor);
        tolua_function(tolua_S, "setColor", lua_cocos2dx_CCNodeRGBA_setColor);
        tolua_function(tolua_S, "isCascadeOpacityEnabled", lua_cocos2dx_CCNodeRGBA_isCascadeOpacityEnabled);
        tolua_function(tolua_S, "getColor", lua_cocos2dx_CCNodeRGBA_getColor);
        tolua_function(tolua_S, "getDisplayedOpacity", lua_cocos2dx_CCNodeRGBA_getDisplayedOpacity);
        tolua_function(tolua_S, "setCascadeColorEnabled", lua_cocos2dx_CCNodeRGBA_setCascadeColorEnabled);
        tolua_function(tolua_S, "setOpacity", lua_cocos2dx_CCNodeRGBA_setOpacity);
        tolua_function(tolua_S, "setCascadeOpacityEnabled", lua_cocos2dx_CCNodeRGBA_setCascadeOpacityEnabled);
        tolua_function(tolua_S, "updateDisplayedOpacity", lua_cocos2dx_CCNodeRGBA_updateDisplayedOpacity);
        tolua_function(tolua_S, "init", lua_cocos2dx_CCNodeRGBA_init);
        tolua_function(tolua_S, "new", lua_cocos2dx_CCNodeRGBA_CCNodeRGBA);
        tolua_function(tolua_S, "setOpacityModifyRGB", lua_cocos2dx_CCNodeRGBA_setOpacityModifyRGB);
        tolua_function(tolua_S, "getOpacity", lua_cocos2dx_CCNodeRGBA_getOpacity);
        tolua_function(tolua_S, "isOpacityModifyRGB", lua_cocos2dx_CCNodeRGBA_isOpacityModifyRGB);
        tolua_function(tolua_S, "isCascadeColorEnabled", lua_cocos2dx_CCNodeRGBA_isCascadeColorEnabled);
        tolua_function(tolua_S, "getDisplayedColor", lua_cocos2dx_CCNodeRGBA_getDisplayedColor);
        tolua_function(tolua_S, "create", lua_cocos2dx_CCNodeRGBA_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::CCNodeRGBA).name();
    g_luaType[typeName] = "CCNodeRGBA";
    g_typeCast["CCNodeRGBA"] = "CCNodeRGBA";
    return 1;
}

TOLUA_API int register_all_cocos2dx(lua_State* tolua_S) {
	tolua_open(tolua_S);
	
	tolua_module(tolua_S, NULL, 0);
	tolua_beginmodule(tolua_S, NULL);

	lua_register_cocos2dx_CCNode(tolua_S);
	lua_register_cocos2dx_CCNodeRGBA(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

