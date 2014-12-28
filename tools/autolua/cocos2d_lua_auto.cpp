/*
** Lua binding: cocos2d
** Generated automatically by tolua++-1.0.92 on Sun Dec 28 20:33:39 2014.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_cocos2d_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SimpleNativeClass (lua_State* tolua_S)
{
 SimpleNativeClass* self = (SimpleNativeClass*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_GLubyte (lua_State* tolua_S)
{
 GLubyte* self = (GLubyte*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_uint32_t (lua_State* tolua_S)
{
 uint32_t* self = (uint32_t*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCLayerColor (lua_State* tolua_S)
{
 CCLayerColor* self = (CCLayerColor*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCLayerRGBA (lua_State* tolua_S)
{
 CCLayerRGBA* self = (CCLayerRGBA*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_ccBlendFunc (lua_State* tolua_S)
{
 ccBlendFunc* self = (ccBlendFunc*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCLayer (lua_State* tolua_S)
{
 CCLayer* self = (CCLayer*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_CCLayerMultiplex (lua_State* tolua_S)
{
 CCLayerMultiplex* self = (CCLayerMultiplex*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SimpleNativeClass");
 tolua_usertype(tolua_S,"CCLayerGradient");
 tolua_usertype(tolua_S,"CCKeypadDelegate");
 tolua_usertype(tolua_S,"CCAccelerometerDelegate");
 tolua_usertype(tolua_S,"GLfloat");
 tolua_usertype(tolua_S,"CCLayerMultiplex");
 tolua_usertype(tolua_S,"CCLayerRGBA");
 tolua_usertype(tolua_S,"ccColor4B");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"CCLayerColor");
 tolua_usertype(tolua_S,"uint32_t");
 tolua_usertype(tolua_S,"GLenum");
 tolua_usertype(tolua_S,"CCBlendProtocol");
 tolua_usertype(tolua_S,"ccBlendFunc");
 tolua_usertype(tolua_S,"GLubyte");
 tolua_usertype(tolua_S,"CCTouchDelegate");
 tolua_usertype(tolua_S,"va_list");
 tolua_usertype(tolua_S,"someStruct1");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"CCRGBAProtocol");
 tolua_usertype(tolua_S,"SimpleNativeClass::someStruct4");
 tolua_usertype(tolua_S,"someStruct2");
 tolua_usertype(tolua_S,"SimpleNativeClass::someStruct3");
}

/* get function: m_owner of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_get_SimpleNativeClass_m_owner_ptr
static int tolua_get_SimpleNativeClass_m_owner_ptr(lua_State* tolua_S)
{
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_owner'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_owner,"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_owner of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_set_SimpleNativeClass_m_owner_ptr
static int tolua_set_SimpleNativeClass_m_owner_ptr(lua_State* tolua_S)
{
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_owner'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_owner = ((CCNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_someOtherField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_get_SimpleNativeClass_m_someOtherField
static int tolua_get_SimpleNativeClass_m_someOtherField(lua_State* tolua_S)
{
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_someOtherField'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_someOtherField);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_someOtherField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_set_SimpleNativeClass_m_someOtherField
static int tolua_set_SimpleNativeClass_m_someOtherField(lua_State* tolua_S)
{
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_someOtherField'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_someOtherField = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_create00
static int tolua_cocos2d_SimpleNativeClass_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SimpleNativeClass* tolua_ret = (SimpleNativeClass*)  SimpleNativeClass::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SimpleNativeClass");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: func of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_func00
static int tolua_cocos2d_SimpleNativeClass_func00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int a = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   SimpleNativeClass::func(a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'func'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: func of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_func01
static int tolua_cocos2d_SimpleNativeClass_func01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   SimpleNativeClass::func();
  }
 }
 return 0;
tolua_lerror:
 return tolua_cocos2d_SimpleNativeClass_func00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnotherMoreComplexField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_getAnotherMoreComplexField00
static int tolua_cocos2d_SimpleNativeClass_getAnotherMoreComplexField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnotherMoreComplexField'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getAnotherMoreComplexField();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnotherMoreComplexField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSomeField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_setSomeField00
static int tolua_cocos2d_SimpleNativeClass_setSomeField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCNode",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  const CCNode* n = ((const CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* pn = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSomeField'", NULL);
#endif
  {
   self->setSomeField(*n,pn);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSomeField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSomeField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_setSomeField01
static int tolua_cocos2d_SimpleNativeClass_setSomeField01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  const int f = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSomeField'", NULL);
#endif
  {
   self->setSomeField(f);
   tolua_pushnumber(tolua_S,(lua_Number)f);
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_SimpleNativeClass_setSomeField00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSomeOtherField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_getSomeOtherField00
static int tolua_cocos2d_SimpleNativeClass_getSomeOtherField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSomeOtherField'", NULL);
#endif
  {
   const int tolua_ret = (const int)  self->getSomeOtherField();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSomeOtherField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSomeOtherField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_setSomeOtherField00
static int tolua_cocos2d_SimpleNativeClass_setSomeOtherField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  int f = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSomeOtherField'", NULL);
#endif
  {
   self->setSomeOtherField(f);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSomeOtherField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: thisReturnsALongLong of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_thisReturnsALongLong00
static int tolua_cocos2d_SimpleNativeClass_thisReturnsALongLong00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'thisReturnsALongLong'", NULL);
#endif
  {
   long long tolua_ret = (long long)  self->thisReturnsALongLong();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'thisReturnsALongLong'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: processSomeStruct4 of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_processSomeStruct400
static int tolua_cocos2d_SimpleNativeClass_processSomeStruct400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SimpleNativeClass::someStruct4",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  SimpleNativeClass::someStruct4* s = ((SimpleNativeClass::someStruct4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'processSomeStruct4'", NULL);
#endif
  {
   int tolua_ret = (int)  self->processSomeStruct4(s);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'processSomeStruct4'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: processSomeEnum3 of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_processSomeEnum300
static int tolua_cocos2d_SimpleNativeClass_processSomeEnum300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  SimpleNativeClass::someEnum3 e = ((SimpleNativeClass::someEnum3) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'processSomeEnum3'", NULL);
#endif
  {
   int tolua_ret = (int)  self->processSomeEnum3(e);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'processSomeEnum3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: processSomeStruct2 of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_processSomeStruct200
static int tolua_cocos2d_SimpleNativeClass_processSomeStruct200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"someStruct2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  someStruct2 s = *((someStruct2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'processSomeStruct2'", NULL);
#endif
  {
   int tolua_ret = (int)  self->processSomeStruct2(s);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'processSomeStruct2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: processSomeStruct3 of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_processSomeStruct300
static int tolua_cocos2d_SimpleNativeClass_processSomeStruct300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SimpleNativeClass::someStruct3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  SimpleNativeClass::someStruct3 s = *((SimpleNativeClass::someStruct3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'processSomeStruct3'", NULL);
#endif
  {
   int tolua_ret = (int)  self->processSomeStruct3(s);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'processSomeStruct3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAge of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_setAge00
static int tolua_cocos2d_SimpleNativeClass_setAge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  int var = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAge'", NULL);
#endif
  {
   self->setAge(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: processSomeStruct1 of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_processSomeStruct100
static int tolua_cocos2d_SimpleNativeClass_processSomeStruct100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"someStruct1",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  someStruct1 s = *((someStruct1*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'processSomeStruct1'", NULL);
#endif
  {
   int tolua_ret = (int)  self->processSomeStruct1(s);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'processSomeStruct1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_init00
static int tolua_cocos2d_SimpleNativeClass_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAge of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_getAge00
static int tolua_cocos2d_SimpleNativeClass_getAge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAge'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAge();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnotherMoreComplexField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_setAnotherMoreComplexField00
static int tolua_cocos2d_SimpleNativeClass_setAnotherMoreComplexField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnotherMoreComplexField'", NULL);
#endif
  {
   self->setAnotherMoreComplexField(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnotherMoreComplexField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: processSomeEnum2 of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_processSomeEnum200
static int tolua_cocos2d_SimpleNativeClass_processSomeEnum200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  someEnum2 e = ((someEnum2) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'processSomeEnum2'", NULL);
#endif
  {
   int tolua_ret = (int)  self->processSomeEnum2(e);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'processSomeEnum2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_new00
static int tolua_cocos2d_SimpleNativeClass_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int m = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   SimpleNativeClass* tolua_ret = (SimpleNativeClass*)  Mtolua_new((SimpleNativeClass)(m));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SimpleNativeClass");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_new00_local
static int tolua_cocos2d_SimpleNativeClass_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int m = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   SimpleNativeClass* tolua_ret = (SimpleNativeClass*)  Mtolua_new((SimpleNativeClass)(m));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SimpleNativeClass");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_new01
static int tolua_cocos2d_SimpleNativeClass_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   SimpleNativeClass* tolua_ret = (SimpleNativeClass*)  Mtolua_new((SimpleNativeClass)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SimpleNativeClass");
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_SimpleNativeClass_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_new01_local
static int tolua_cocos2d_SimpleNativeClass_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   SimpleNativeClass* tolua_ret = (SimpleNativeClass*)  Mtolua_new((SimpleNativeClass)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SimpleNativeClass");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_SimpleNativeClass_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_new02
static int tolua_cocos2d_SimpleNativeClass_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int m1 = ((int)  tolua_tonumber(tolua_S,2,0));
  int m2 = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   SimpleNativeClass* tolua_ret = (SimpleNativeClass*)  Mtolua_new((SimpleNativeClass)(m1,m2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SimpleNativeClass");
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_SimpleNativeClass_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_new02_local
static int tolua_cocos2d_SimpleNativeClass_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int m1 = ((int)  tolua_tonumber(tolua_S,2,0));
  int m2 = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   SimpleNativeClass* tolua_ret = (SimpleNativeClass*)  Mtolua_new((SimpleNativeClass)(m1,m2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SimpleNativeClass");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_SimpleNativeClass_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: processClassEnum of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_processClassEnum00
static int tolua_cocos2d_SimpleNativeClass_processClassEnum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  SimpleNativeClass::someClassEnum e = ((SimpleNativeClass::someClassEnum) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'processClassEnum'", NULL);
#endif
  {
   int tolua_ret = (int)  self->processClassEnum(e);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'processClassEnum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_delete00
static int tolua_cocos2d_SimpleNativeClass_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getObjectType of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_getObjectType00
static int tolua_cocos2d_SimpleNativeClass_getObjectType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getObjectType'", NULL);
#endif
  {
   uint32_t tolua_ret = (uint32_t)  self->getObjectType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint32_t)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint32_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint32_t));
     tolua_pushusertype(tolua_S,tolua_obj,"uint32_t");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getObjectType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: processGLubyte of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_processGLubyte00
static int tolua_cocos2d_SimpleNativeClass_processGLubyte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  GLubyte b = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'processGLubyte'", NULL);
#endif
  {
   int tolua_ret = (int)  self->processGLubyte(b);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'processGLubyte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: t of class  someStruct4 */
#ifndef TOLUA_DISABLE_tolua_get_SimpleNativeClass__someStruct4_t_ptr
static int tolua_get_SimpleNativeClass__someStruct4_t_ptr(lua_State* tolua_S)
{
  SimpleNativeClass::someStruct4* self = (SimpleNativeClass::someStruct4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 't'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->t,"CCLayer");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: t of class  someStruct4 */
#ifndef TOLUA_DISABLE_tolua_set_SimpleNativeClass__someStruct4_t_ptr
static int tolua_set_SimpleNativeClass__someStruct4_t_ptr(lua_State* tolua_S)
{
  SimpleNativeClass::someStruct4* self = (SimpleNativeClass::someStruct4*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 't'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCLayer",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->t = ((CCLayer*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: n of class  someStruct3 */
#ifndef TOLUA_DISABLE_tolua_get_SimpleNativeClass__someStruct3_n_ptr
static int tolua_get_SimpleNativeClass__someStruct3_n_ptr(lua_State* tolua_S)
{
  SimpleNativeClass::someStruct3* self = (SimpleNativeClass::someStruct3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'n'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->n,"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: n of class  someStruct3 */
#ifndef TOLUA_DISABLE_tolua_set_SimpleNativeClass__someStruct3_n_ptr
static int tolua_set_SimpleNativeClass__someStruct3_n_ptr(lua_State* tolua_S)
{
  SimpleNativeClass::someStruct3* self = (SimpleNativeClass::someStruct3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'n'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->n = ((CCNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: test of class  someStruct3 */
#ifndef TOLUA_DISABLE_tolua_cocos2d_SimpleNativeClass_someStruct3_test00
static int tolua_cocos2d_SimpleNativeClass_someStruct3_test00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass::someStruct3",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass::someStruct3* self = (SimpleNativeClass::someStruct3*)  tolua_tousertype(tolua_S,1,0);
  const int f = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'test'", NULL);
#endif
  {
   self->test(f);
   tolua_pushnumber(tolua_S,(lua_Number)f);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'test'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_create00
static int tolua_cocos2d_CCLayer_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayer* tolua_ret = (CCLayer*)  CCLayer::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptTouchHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_unregisterScriptTouchHandler00
static int tolua_cocos2d_CCLayer_unregisterScriptTouchHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptTouchHandler'", NULL);
#endif
  {
   self->unregisterScriptTouchHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptTouchHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnter of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_onEnter00
static int tolua_cocos2d_CCLayer_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnter'", NULL);
#endif
  {
   self->onEnter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: keyBackClicked of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_keyBackClicked00
static int tolua_cocos2d_CCLayer_keyBackClicked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'keyBackClicked'", NULL);
#endif
  {
   self->keyBackClicked();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'keyBackClicked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAccelerometerInterval of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_setAccelerometerInterval00
static int tolua_cocos2d_CCLayer_setAccelerometerInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  double interval = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAccelerometerInterval'", NULL);
#endif
  {
   self->setAccelerometerInterval(interval);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAccelerometerInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptAccelerateHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_unregisterScriptAccelerateHandler00
static int tolua_cocos2d_CCLayer_unregisterScriptAccelerateHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptAccelerateHandler'", NULL);
#endif
  {
   self->unregisterScriptAccelerateHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptAccelerateHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptAccelerateHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_registerScriptAccelerateHandler00
static int tolua_cocos2d_CCLayer_registerScriptAccelerateHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptAccelerateHandler'", NULL);
#endif
  {
   self->registerScriptAccelerateHandler(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptAccelerateHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchMode of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_getTouchMode00
static int tolua_cocos2d_CCLayer_getTouchMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchMode'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTouchMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAccelerometerEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_setAccelerometerEnabled00
static int tolua_cocos2d_CCLayer_setAccelerometerEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAccelerometerEnabled'", NULL);
#endif
  {
   self->setAccelerometerEnabled(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAccelerometerEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isSwallowTouch of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_isSwallowTouch00
static int tolua_cocos2d_CCLayer_isSwallowTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isSwallowTouch'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isSwallowTouch();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSwallowTouch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_init00
static int tolua_cocos2d_CCLayer_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_delete00
static int tolua_cocos2d_CCLayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_isTouchEnabled00
static int tolua_cocos2d_CCLayer_isTouchEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTouchEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTouchEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_setTouchEnabled00
static int tolua_cocos2d_CCLayer_setTouchEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEnabled'", NULL);
#endif
  {
   self->setTouchEnabled(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptKeypadHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_unregisterScriptKeypadHandler00
static int tolua_cocos2d_CCLayer_unregisterScriptKeypadHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptKeypadHandler'", NULL);
#endif
  {
   self->unregisterScriptKeypadHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptKeypadHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSwallowTouch of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_setSwallowTouch00
static int tolua_cocos2d_CCLayer_setSwallowTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSwallowTouch'", NULL);
#endif
  {
   self->setSwallowTouch(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSwallowTouch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isKeypadEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_isKeypadEnabled00
static int tolua_cocos2d_CCLayer_isKeypadEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isKeypadEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isKeypadEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isKeypadEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchMode of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_setTouchMode00
static int tolua_cocos2d_CCLayer_setTouchMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  ccTouchesMode mode = ((ccTouchesMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchMode'", NULL);
#endif
  {
   self->setTouchMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isAccelerometerEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_isAccelerometerEnabled00
static int tolua_cocos2d_CCLayer_isAccelerometerEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isAccelerometerEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isAccelerometerEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isAccelerometerEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onExit of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_onExit00
static int tolua_cocos2d_CCLayer_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onExit'", NULL);
#endif
  {
   self->onExit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptTouchHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_registerScriptTouchHandler00
static int tolua_cocos2d_CCLayer_registerScriptTouchHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = ((int)  tolua_tonumber(tolua_S,2,0));
  bool bIsMultiTouches = ((bool)  tolua_toboolean(tolua_S,3,0));
  int nPriority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool bSwallowsTouches = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptTouchHandler'", NULL);
#endif
  {
   self->registerScriptTouchHandler(nHandler,bIsMultiTouches,nPriority,bSwallowsTouches);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptTouchHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchPriority of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_setTouchPriority00
static int tolua_cocos2d_CCLayer_setTouchPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchPriority'", NULL);
#endif
  {
   self->setTouchPriority(priority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_new00
static int tolua_cocos2d_CCLayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayer* tolua_ret = (CCLayer*)  Mtolua_new((CCLayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_new00_local
static int tolua_cocos2d_CCLayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayer* tolua_ret = (CCLayer*)  Mtolua_new((CCLayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchPriority of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_getTouchPriority00
static int tolua_cocos2d_CCLayer_getTouchPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTouchPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setKeypadEnabled of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_setKeypadEnabled00
static int tolua_cocos2d_CCLayer_setKeypadEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setKeypadEnabled'", NULL);
#endif
  {
   self->setKeypadEnabled(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setKeypadEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_registerWithTouchDispatcher00
static int tolua_cocos2d_CCLayer_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: keyMenuClicked of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_keyMenuClicked00
static int tolua_cocos2d_CCLayer_keyMenuClicked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'keyMenuClicked'", NULL);
#endif
  {
   self->keyMenuClicked();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'keyMenuClicked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnterTransitionDidFinish of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_onEnterTransitionDidFinish00
static int tolua_cocos2d_CCLayer_onEnterTransitionDidFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnterTransitionDidFinish'", NULL);
#endif
  {
   self->onEnterTransitionDidFinish();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnterTransitionDidFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptKeypadHandler of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayer_registerScriptKeypadHandler00
static int tolua_cocos2d_CCLayer_registerScriptKeypadHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
  int nHandler = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptKeypadHandler'", NULL);
#endif
  {
   self->registerScriptKeypadHandler(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptKeypadHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCTouchDelegate__ of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCLayer___CCTouchDelegate__
static int tolua_get_CCLayer___CCTouchDelegate__(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTouchDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTouchDelegate*>(self), "CCTouchDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTouchDelegate*)self), "CCTouchDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCAccelerometerDelegate__ of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCLayer___CCAccelerometerDelegate__
static int tolua_get_CCLayer___CCAccelerometerDelegate__(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCAccelerometerDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCAccelerometerDelegate*>(self), "CCAccelerometerDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCAccelerometerDelegate*)self), "CCAccelerometerDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCKeypadDelegate__ of class  CCLayer */
#ifndef TOLUA_DISABLE_tolua_get_CCLayer___CCKeypadDelegate__
static int tolua_get_CCLayer___CCKeypadDelegate__(lua_State* tolua_S)
{
  CCLayer* self = (CCLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCKeypadDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCKeypadDelegate*>(self), "CCKeypadDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCKeypadDelegate*)self), "CCKeypadDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithLayer of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_createWithLayer00
static int tolua_cocos2d_CCLayerMultiplex_createWithLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayer* layer = ((CCLayer*)  tolua_tousertype(tolua_S,2,0));
  {
   CCLayerMultiplex* tolua_ret = (CCLayerMultiplex*)  CCLayerMultiplex::createWithLayer(layer);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerMultiplex");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_create00
static int tolua_cocos2d_CCLayerMultiplex_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayerMultiplex* tolua_ret = (CCLayerMultiplex*)  CCLayerMultiplex::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerMultiplex");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEnabledLayer of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_getEnabledLayer00
static int tolua_cocos2d_CCLayerMultiplex_getEnabledLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerMultiplex* self = (CCLayerMultiplex*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEnabledLayer'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getEnabledLayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEnabledLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_delete00
static int tolua_cocos2d_CCLayerMultiplex_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerMultiplex* self = (CCLayerMultiplex*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_new00
static int tolua_cocos2d_CCLayerMultiplex_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayerMultiplex* tolua_ret = (CCLayerMultiplex*)  Mtolua_new((CCLayerMultiplex)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerMultiplex");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_new00_local
static int tolua_cocos2d_CCLayerMultiplex_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayerMultiplex* tolua_ret = (CCLayerMultiplex*)  Mtolua_new((CCLayerMultiplex)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerMultiplex");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: layerAt of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_layerAt00
static int tolua_cocos2d_CCLayerMultiplex_layerAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerMultiplex* self = (CCLayerMultiplex*)  tolua_tousertype(tolua_S,1,0);
  int n = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'layerAt'", NULL);
#endif
  {
   CCLayer* tolua_ret = (CCLayer*)  self->layerAt(n);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'layerAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addLayer of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_addLayer00
static int tolua_cocos2d_CCLayerMultiplex_addLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerMultiplex* self = (CCLayerMultiplex*)  tolua_tousertype(tolua_S,1,0);
  CCLayer* layer = ((CCLayer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addLayer'", NULL);
#endif
  {
   self->addLayer(layer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithLayers of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_initWithLayers00
static int tolua_cocos2d_CCLayerMultiplex_initWithLayers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCLayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"va_list",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerMultiplex* self = (CCLayerMultiplex*)  tolua_tousertype(tolua_S,1,0);
  CCLayer* layer = ((CCLayer*)  tolua_tousertype(tolua_S,2,0));
  va_list params = *((va_list*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithLayers'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithLayers(layer,params);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithLayers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: switchTo of class  CCLayerMultiplex */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerMultiplex_switchTo00
static int tolua_cocos2d_CCLayerMultiplex_switchTo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerMultiplex",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerMultiplex* self = (CCLayerMultiplex*)  tolua_tousertype(tolua_S,1,0);
  unsigned int n = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'switchTo'", NULL);
#endif
  {
   self->switchTo(n);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'switchTo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_create00
static int tolua_cocos2d_CCLayerGradient_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ccColor4B* start = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  const ccColor4B* end = ((const ccColor4B*)  tolua_tousertype(tolua_S,3,0));
  {
   CCLayerGradient* tolua_ret = (CCLayerGradient*)  CCLayerGradient::create(*start,*end);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerGradient");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_create01
static int tolua_cocos2d_CCLayerGradient_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CCLayerGradient* tolua_ret = (CCLayerGradient*)  CCLayerGradient::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerGradient");
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_CCLayerGradient_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStartColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_getStartColor00
static int tolua_cocos2d_CCLayerGradient_getStartColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStartColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getStartColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStartColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCompressedInterpolation of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_isCompressedInterpolation00
static int tolua_cocos2d_CCLayerGradient_isCompressedInterpolation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCompressedInterpolation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCompressedInterpolation();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCompressedInterpolation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStartOpacity of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_getStartOpacity00
static int tolua_cocos2d_CCLayerGradient_getStartOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStartOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getStartOpacity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((GLubyte)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLubyte));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStartOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStartOpacity of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_setStartOpacity00
static int tolua_cocos2d_CCLayerGradient_setStartOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
  GLubyte var = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStartOpacity'", NULL);
#endif
  {
   self->setStartOpacity(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStartOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCompressedInterpolation of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_setCompressedInterpolation00
static int tolua_cocos2d_CCLayerGradient_setCompressedInterpolation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
  bool bCompressedInterpolation = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCompressedInterpolation'", NULL);
#endif
  {
   self->setCompressedInterpolation(bCompressedInterpolation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCompressedInterpolation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEndOpacity of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_setEndOpacity00
static int tolua_cocos2d_CCLayerGradient_setEndOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
  GLubyte var = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEndOpacity'", NULL);
#endif
  {
   self->setEndOpacity(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEndOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_init00
static int tolua_cocos2d_CCLayerGradient_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEndColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_setEndColor00
static int tolua_cocos2d_CCLayerGradient_setEndColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* var = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEndColor'", NULL);
#endif
  {
   self->setEndColor(*var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEndColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_initWithColor00
static int tolua_cocos2d_CCLayerGradient_initWithColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* start = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  const ccColor4B* end = ((const ccColor4B*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithColor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithColor(*start,*end);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEndColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_getEndColor00
static int tolua_cocos2d_CCLayerGradient_getEndColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEndColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getEndColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEndColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEndOpacity of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_getEndOpacity00
static int tolua_cocos2d_CCLayerGradient_getEndOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEndOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getEndOpacity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((GLubyte)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLubyte));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEndOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStartColor of class  CCLayerGradient */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerGradient_setStartColor00
static int tolua_cocos2d_CCLayerGradient_setStartColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerGradient",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerGradient* self = (CCLayerGradient*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* var = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStartColor'", NULL);
#endif
  {
   self->setStartColor(*var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStartColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_create00
static int tolua_cocos2d_CCLayerRGBA_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayerRGBA* tolua_ret = (CCLayerRGBA*)  CCLayerRGBA::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerRGBA");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateDisplayedColor of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_updateDisplayedColor00
static int tolua_cocos2d_CCLayerRGBA_updateDisplayedColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* parentColor = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateDisplayedColor'", NULL);
#endif
  {
   self->updateDisplayedColor(*parentColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateDisplayedColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_setColor00
static int tolua_cocos2d_CCLayerRGBA_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCascadeOpacityEnabled of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_isCascadeOpacityEnabled00
static int tolua_cocos2d_CCLayerRGBA_isCascadeOpacityEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCascadeOpacityEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCascadeOpacityEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCascadeOpacityEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColor of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_getColor00
static int tolua_cocos2d_CCLayerRGBA_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayedOpacity of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_getDisplayedOpacity00
static int tolua_cocos2d_CCLayerRGBA_getDisplayedOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayedOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getDisplayedOpacity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((GLubyte)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLubyte));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayedOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCascadeColorEnabled of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_setCascadeColorEnabled00
static int tolua_cocos2d_CCLayerRGBA_setCascadeColorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
  bool cascadeColorEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCascadeColorEnabled'", NULL);
#endif
  {
   self->setCascadeColorEnabled(cascadeColorEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCascadeColorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_setOpacity00
static int tolua_cocos2d_CCLayerRGBA_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_delete00
static int tolua_cocos2d_CCLayerRGBA_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCascadeOpacityEnabled of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_setCascadeOpacityEnabled00
static int tolua_cocos2d_CCLayerRGBA_setCascadeOpacityEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
  bool cascadeOpacityEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCascadeOpacityEnabled'", NULL);
#endif
  {
   self->setCascadeOpacityEnabled(cascadeOpacityEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCascadeOpacityEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateDisplayedOpacity of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_updateDisplayedOpacity00
static int tolua_cocos2d_CCLayerRGBA_updateDisplayedOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
  GLubyte parentOpacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateDisplayedOpacity'", NULL);
#endif
  {
   self->updateDisplayedOpacity(parentOpacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateDisplayedOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_init00
static int tolua_cocos2d_CCLayerRGBA_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_new00
static int tolua_cocos2d_CCLayerRGBA_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayerRGBA* tolua_ret = (CCLayerRGBA*)  Mtolua_new((CCLayerRGBA)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerRGBA");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_new00_local
static int tolua_cocos2d_CCLayerRGBA_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayerRGBA* tolua_ret = (CCLayerRGBA*)  Mtolua_new((CCLayerRGBA)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerRGBA");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacityModifyRGB of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_setOpacityModifyRGB00
static int tolua_cocos2d_CCLayerRGBA_setOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
  bool bValue = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacityModifyRGB'", NULL);
#endif
  {
   self->setOpacityModifyRGB(bValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpacity of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_getOpacity00
static int tolua_cocos2d_CCLayerRGBA_getOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getOpacity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((GLubyte)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLubyte));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOpacityModifyRGB of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_isOpacityModifyRGB00
static int tolua_cocos2d_CCLayerRGBA_isOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOpacityModifyRGB'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOpacityModifyRGB();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCascadeColorEnabled of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_isCascadeColorEnabled00
static int tolua_cocos2d_CCLayerRGBA_isCascadeColorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCascadeColorEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCascadeColorEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCascadeColorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayedColor of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerRGBA_getDisplayedColor00
static int tolua_cocos2d_CCLayerRGBA_getDisplayedColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerRGBA",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayedColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getDisplayedColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayedColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCRGBAProtocol__ of class  CCLayerRGBA */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerRGBA___CCRGBAProtocol__
static int tolua_get_CCLayerRGBA___CCRGBAProtocol__(lua_State* tolua_S)
{
  CCLayerRGBA* self = (CCLayerRGBA*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCRGBAProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCRGBAProtocol*>(self), "CCRGBAProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((CCRGBAProtocol*)self), "CCRGBAProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_create00
static int tolua_cocos2d_CCLayerColor_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"GLfloat",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"GLfloat",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  GLfloat width = *((GLfloat*)  tolua_tousertype(tolua_S,3,0));
  GLfloat height = *((GLfloat*)  tolua_tousertype(tolua_S,4,0));
  {
   CCLayerColor* tolua_ret = (CCLayerColor*)  CCLayerColor::create(*color,width,height);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerColor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_create01
static int tolua_cocos2d_CCLayerColor_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CCLayerColor* tolua_ret = (CCLayerColor*)  CCLayerColor::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerColor");
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_CCLayerColor_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_create02
static int tolua_cocos2d_CCLayerColor_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  {
   CCLayerColor* tolua_ret = (CCLayerColor*)  CCLayerColor::create(*color);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerColor");
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_CCLayerColor_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_draw00
static int tolua_cocos2d_CCLayerColor_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendFunc of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_getBlendFunc00
static int tolua_cocos2d_CCLayerColor_getBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendFunc'", NULL);
#endif
  {
   ccBlendFunc tolua_ret = (ccBlendFunc)  self->getBlendFunc();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccBlendFunc)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccBlendFunc));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_setColor00
static int tolua_cocos2d_CCLayerColor_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendFunc of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_setBlendFunc00
static int tolua_cocos2d_CCLayerColor_setBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
  ccBlendFunc var = *((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendFunc'", NULL);
#endif
  {
   self->setBlendFunc(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeWidth of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_changeWidth00
static int tolua_cocos2d_CCLayerColor_changeWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLfloat",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
  GLfloat w = *((GLfloat*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeWidth'", NULL);
#endif
  {
   self->changeWidth(w);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeWidthAndHeight of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_changeWidthAndHeight00
static int tolua_cocos2d_CCLayerColor_changeWidthAndHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLfloat",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"GLfloat",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
  GLfloat w = *((GLfloat*)  tolua_tousertype(tolua_S,2,0));
  GLfloat h = *((GLfloat*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeWidthAndHeight'", NULL);
#endif
  {
   self->changeWidthAndHeight(w,h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeWidthAndHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_delete00
static int tolua_cocos2d_CCLayerColor_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_init00
static int tolua_cocos2d_CCLayerColor_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithColor of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_initWithColor00
static int tolua_cocos2d_CCLayerColor_initWithColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithColor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithColor(*color);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithColor of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_initWithColor01
static int tolua_cocos2d_CCLayerColor_initWithColor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"GLfloat",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"GLfloat",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  GLfloat width = *((GLfloat*)  tolua_tousertype(tolua_S,3,0));
  GLfloat height = *((GLfloat*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithColor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithColor(*color,width,height);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_cocos2d_CCLayerColor_initWithColor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_new00
static int tolua_cocos2d_CCLayerColor_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayerColor* tolua_ret = (CCLayerColor*)  Mtolua_new((CCLayerColor)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerColor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_new00_local
static int tolua_cocos2d_CCLayerColor_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCLayerColor* tolua_ret = (CCLayerColor*)  Mtolua_new((CCLayerColor)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayerColor");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_setOpacity00
static int tolua_cocos2d_CCLayerColor_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeHeight of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_cocos2d_CCLayerColor_changeHeight00
static int tolua_cocos2d_CCLayerColor_changeHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLfloat",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
  GLfloat h = *((GLfloat*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeHeight'", NULL);
#endif
  {
   self->changeHeight(h);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCBlendProtocol__ of class  CCLayerColor */
#ifndef TOLUA_DISABLE_tolua_get_CCLayerColor___CCBlendProtocol__
static int tolua_get_CCLayerColor___CCBlendProtocol__(lua_State* tolua_S)
{
  CCLayerColor* self = (CCLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCBlendProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCBlendProtocol*>(self), "CCBlendProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((CCBlendProtocol*)self), "CCBlendProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: i of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_get_someStruct2_i
static int tolua_get_someStruct2_i(lua_State* tolua_S)
{
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'i'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->i);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: i of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_set_someStruct2_i
static int tolua_set_someStruct2_i(lua_State* tolua_S)
{
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'i'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->i = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: f of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_get_someStruct2_f
static int tolua_get_someStruct2_f(lua_State* tolua_S)
{
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'f'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->f);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: f of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_set_someStruct2_f
static int tolua_set_someStruct2_f(lua_State* tolua_S)
{
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'f'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->f = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: d of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_get_someStruct2_d
static int tolua_get_someStruct2_d(lua_State* tolua_S)
{
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'd'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->d);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: d of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_set_someStruct2_d
static int tolua_set_someStruct2_d(lua_State* tolua_S)
{
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'd'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->d = ((double)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: n of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_get_someStruct2_n_ptr
static int tolua_get_someStruct2_n_ptr(lua_State* tolua_S)
{
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'n'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->n,"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: n of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_set_someStruct2_n_ptr
static int tolua_set_someStruct2_n_ptr(lua_State* tolua_S)
{
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'n'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->n = ((CCNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: test of class  someStruct2 */
#ifndef TOLUA_DISABLE_tolua_cocos2d_someStruct2_test00
static int tolua_cocos2d_someStruct2_test00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"someStruct2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  someStruct2* self = (someStruct2*)  tolua_tousertype(tolua_S,1,0);
  const int f = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'test'", NULL);
#endif
  {
   self->test(f);
   tolua_pushnumber(tolua_S,(lua_Number)f);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'test'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: r of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor4B_r
static int tolua_get_ccColor4B_r(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->r,"GLubyte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: r of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor4B_r
static int tolua_set_ccColor4B_r(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->r = *((GLubyte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: g of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor4B_g
static int tolua_get_ccColor4B_g(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->g,"GLubyte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: g of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor4B_g
static int tolua_set_ccColor4B_g(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->g = *((GLubyte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor4B_b
static int tolua_get_ccColor4B_b(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->b,"GLubyte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor4B_b
static int tolua_set_ccColor4B_b(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b = *((GLubyte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: a of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor4B_a
static int tolua_get_ccColor4B_a(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'a'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->a,"GLubyte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: a of class  ccColor4B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor4B_a
static int tolua_set_ccColor4B_a(lua_State* tolua_S)
{
  ccColor4B* self = (ccColor4B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'a'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->a = *((GLubyte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: src of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_get_ccBlendFunc_src
static int tolua_get_ccBlendFunc_src(lua_State* tolua_S)
{
  ccBlendFunc* self = (ccBlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'src'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->src,"GLenum");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: src of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_set_ccBlendFunc_src
static int tolua_set_ccBlendFunc_src(lua_State* tolua_S)
{
  ccBlendFunc* self = (ccBlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'src'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLenum",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->src = *((GLenum*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: dst of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_get_ccBlendFunc_dst
static int tolua_get_ccBlendFunc_dst(lua_State* tolua_S)
{
  ccBlendFunc* self = (ccBlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dst'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->dst,"GLenum");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: dst of class  ccBlendFunc */
#ifndef TOLUA_DISABLE_tolua_set_ccBlendFunc_dst
static int tolua_set_ccBlendFunc_dst(lua_State* tolua_S)
{
  ccBlendFunc* self = (ccBlendFunc*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'dst'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLenum",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->dst = *((GLenum*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: n of class  someStruct1 */
#ifndef TOLUA_DISABLE_tolua_get_someStruct1_n_ptr
static int tolua_get_someStruct1_n_ptr(lua_State* tolua_S)
{
  someStruct1* self = (someStruct1*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'n'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->n,"CCNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: n of class  someStruct1 */
#ifndef TOLUA_DISABLE_tolua_set_someStruct1_n_ptr
static int tolua_set_someStruct1_n_ptr(lua_State* tolua_S)
{
  someStruct1* self = (someStruct1*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'n'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->n = ((CCNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: test of class  someStruct1 */
#ifndef TOLUA_DISABLE_tolua_cocos2d_someStruct1_test00
static int tolua_cocos2d_someStruct1_test00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"someStruct1",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  someStruct1* self = (someStruct1*)  tolua_tousertype(tolua_S,1,0);
  const int f = ((const int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'test'", NULL);
#endif
  {
   self->test(f);
   tolua_pushnumber(tolua_S,(lua_Number)f);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'test'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: r of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor3B_r
static int tolua_get_ccColor3B_r(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->r,"GLubyte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: r of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor3B_r
static int tolua_set_ccColor3B_r(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'r'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->r = *((GLubyte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: g of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor3B_g
static int tolua_get_ccColor3B_g(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->g,"GLubyte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: g of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor3B_g
static int tolua_set_ccColor3B_g(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'g'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->g = *((GLubyte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: b of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_get_ccColor3B_b
static int tolua_get_ccColor3B_b(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->b,"GLubyte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: b of class  ccColor3B */
#ifndef TOLUA_DISABLE_tolua_set_ccColor3B_b
static int tolua_set_ccColor3B_b(lua_State* tolua_S)
{
  ccColor3B* self = (ccColor3B*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'b'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->b = *((GLubyte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_cocos2d_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SimpleNativeClass","SimpleNativeClass","CCNode",tolua_collect_SimpleNativeClass);
  #else
  tolua_cclass(tolua_S,"SimpleNativeClass","SimpleNativeClass","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SimpleNativeClass");
   tolua_variable(tolua_S,"m_owner",tolua_get_SimpleNativeClass_m_owner_ptr,tolua_set_SimpleNativeClass_m_owner_ptr);
   tolua_variable(tolua_S,"m_someOtherField",tolua_get_SimpleNativeClass_m_someOtherField,tolua_set_SimpleNativeClass_m_someOtherField);
   tolua_function(tolua_S,"create",tolua_cocos2d_SimpleNativeClass_create00);
   tolua_function(tolua_S,"func",tolua_cocos2d_SimpleNativeClass_func00);
   tolua_function(tolua_S,"func",tolua_cocos2d_SimpleNativeClass_func01);
   tolua_function(tolua_S,"getAnotherMoreComplexField",tolua_cocos2d_SimpleNativeClass_getAnotherMoreComplexField00);
   tolua_function(tolua_S,"setSomeField",tolua_cocos2d_SimpleNativeClass_setSomeField00);
   tolua_function(tolua_S,"setSomeField",tolua_cocos2d_SimpleNativeClass_setSomeField01);
   tolua_function(tolua_S,"getSomeOtherField",tolua_cocos2d_SimpleNativeClass_getSomeOtherField00);
   tolua_function(tolua_S,"setSomeOtherField",tolua_cocos2d_SimpleNativeClass_setSomeOtherField00);
   tolua_function(tolua_S,"thisReturnsALongLong",tolua_cocos2d_SimpleNativeClass_thisReturnsALongLong00);
   tolua_function(tolua_S,"processSomeStruct4",tolua_cocos2d_SimpleNativeClass_processSomeStruct400);
   tolua_function(tolua_S,"processSomeEnum3",tolua_cocos2d_SimpleNativeClass_processSomeEnum300);
   tolua_function(tolua_S,"processSomeStruct2",tolua_cocos2d_SimpleNativeClass_processSomeStruct200);
   tolua_function(tolua_S,"processSomeStruct3",tolua_cocos2d_SimpleNativeClass_processSomeStruct300);
   tolua_function(tolua_S,"setAge",tolua_cocos2d_SimpleNativeClass_setAge00);
   tolua_function(tolua_S,"processSomeStruct1",tolua_cocos2d_SimpleNativeClass_processSomeStruct100);
   tolua_function(tolua_S,"init",tolua_cocos2d_SimpleNativeClass_init00);
   tolua_function(tolua_S,"getAge",tolua_cocos2d_SimpleNativeClass_getAge00);
   tolua_function(tolua_S,"setAnotherMoreComplexField",tolua_cocos2d_SimpleNativeClass_setAnotherMoreComplexField00);
   tolua_function(tolua_S,"processSomeEnum2",tolua_cocos2d_SimpleNativeClass_processSomeEnum200);
   tolua_function(tolua_S,"new",tolua_cocos2d_SimpleNativeClass_new00);
   tolua_function(tolua_S,"new_local",tolua_cocos2d_SimpleNativeClass_new00_local);
   tolua_function(tolua_S,".call",tolua_cocos2d_SimpleNativeClass_new00_local);
   tolua_function(tolua_S,"new",tolua_cocos2d_SimpleNativeClass_new01);
   tolua_function(tolua_S,"new_local",tolua_cocos2d_SimpleNativeClass_new01_local);
   tolua_function(tolua_S,".call",tolua_cocos2d_SimpleNativeClass_new01_local);
   tolua_function(tolua_S,"new",tolua_cocos2d_SimpleNativeClass_new02);
   tolua_function(tolua_S,"new_local",tolua_cocos2d_SimpleNativeClass_new02_local);
   tolua_function(tolua_S,".call",tolua_cocos2d_SimpleNativeClass_new02_local);
   tolua_function(tolua_S,"processClassEnum",tolua_cocos2d_SimpleNativeClass_processClassEnum00);
   tolua_function(tolua_S,"delete",tolua_cocos2d_SimpleNativeClass_delete00);
   tolua_function(tolua_S,"getObjectType",tolua_cocos2d_SimpleNativeClass_getObjectType00);
   tolua_function(tolua_S,"processGLubyte",tolua_cocos2d_SimpleNativeClass_processGLubyte00);
   tolua_constant(tolua_S,"kValue5",SimpleNativeClass::kValue5);
   tolua_constant(tolua_S,"kValue6",SimpleNativeClass::kValue6);
   tolua_constant(tolua_S,"kValue101",SimpleNativeClass::kValue101);
   tolua_cclass(tolua_S,"someStruct4","SimpleNativeClass::someStruct4","",NULL);
   tolua_beginmodule(tolua_S,"someStruct4");
    tolua_variable(tolua_S,"t",tolua_get_SimpleNativeClass__someStruct4_t_ptr,tolua_set_SimpleNativeClass__someStruct4_t_ptr);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"someStruct3","SimpleNativeClass::someStruct3","",NULL);
   tolua_beginmodule(tolua_S,"someStruct3");
    tolua_variable(tolua_S,"n",tolua_get_SimpleNativeClass__someStruct3_n_ptr,tolua_set_SimpleNativeClass__someStruct3_n_ptr);
    tolua_function(tolua_S,"test",tolua_cocos2d_SimpleNativeClass_someStruct3_test00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCLayer","CCLayer","CCNode",tolua_collect_CCLayer);
  #else
  tolua_cclass(tolua_S,"CCLayer","CCLayer","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCLayer");
   tolua_function(tolua_S,"create",tolua_cocos2d_CCLayer_create00);
   tolua_function(tolua_S,"unregisterScriptTouchHandler",tolua_cocos2d_CCLayer_unregisterScriptTouchHandler00);
   tolua_function(tolua_S,"onEnter",tolua_cocos2d_CCLayer_onEnter00);
   tolua_function(tolua_S,"keyBackClicked",tolua_cocos2d_CCLayer_keyBackClicked00);
   tolua_function(tolua_S,"setAccelerometerInterval",tolua_cocos2d_CCLayer_setAccelerometerInterval00);
   tolua_function(tolua_S,"unregisterScriptAccelerateHandler",tolua_cocos2d_CCLayer_unregisterScriptAccelerateHandler00);
   tolua_function(tolua_S,"registerScriptAccelerateHandler",tolua_cocos2d_CCLayer_registerScriptAccelerateHandler00);
   tolua_function(tolua_S,"getTouchMode",tolua_cocos2d_CCLayer_getTouchMode00);
   tolua_function(tolua_S,"setAccelerometerEnabled",tolua_cocos2d_CCLayer_setAccelerometerEnabled00);
   tolua_function(tolua_S,"isSwallowTouch",tolua_cocos2d_CCLayer_isSwallowTouch00);
   tolua_function(tolua_S,"init",tolua_cocos2d_CCLayer_init00);
   tolua_function(tolua_S,"delete",tolua_cocos2d_CCLayer_delete00);
   tolua_function(tolua_S,"isTouchEnabled",tolua_cocos2d_CCLayer_isTouchEnabled00);
   tolua_function(tolua_S,"setTouchEnabled",tolua_cocos2d_CCLayer_setTouchEnabled00);
   tolua_function(tolua_S,"unregisterScriptKeypadHandler",tolua_cocos2d_CCLayer_unregisterScriptKeypadHandler00);
   tolua_function(tolua_S,"setSwallowTouch",tolua_cocos2d_CCLayer_setSwallowTouch00);
   tolua_function(tolua_S,"isKeypadEnabled",tolua_cocos2d_CCLayer_isKeypadEnabled00);
   tolua_function(tolua_S,"setTouchMode",tolua_cocos2d_CCLayer_setTouchMode00);
   tolua_function(tolua_S,"isAccelerometerEnabled",tolua_cocos2d_CCLayer_isAccelerometerEnabled00);
   tolua_function(tolua_S,"onExit",tolua_cocos2d_CCLayer_onExit00);
   tolua_function(tolua_S,"registerScriptTouchHandler",tolua_cocos2d_CCLayer_registerScriptTouchHandler00);
   tolua_function(tolua_S,"setTouchPriority",tolua_cocos2d_CCLayer_setTouchPriority00);
   tolua_function(tolua_S,"new",tolua_cocos2d_CCLayer_new00);
   tolua_function(tolua_S,"new_local",tolua_cocos2d_CCLayer_new00_local);
   tolua_function(tolua_S,".call",tolua_cocos2d_CCLayer_new00_local);
   tolua_function(tolua_S,"getTouchPriority",tolua_cocos2d_CCLayer_getTouchPriority00);
   tolua_function(tolua_S,"setKeypadEnabled",tolua_cocos2d_CCLayer_setKeypadEnabled00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_cocos2d_CCLayer_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"keyMenuClicked",tolua_cocos2d_CCLayer_keyMenuClicked00);
   tolua_function(tolua_S,"onEnterTransitionDidFinish",tolua_cocos2d_CCLayer_onEnterTransitionDidFinish00);
   tolua_function(tolua_S,"registerScriptKeypadHandler",tolua_cocos2d_CCLayer_registerScriptKeypadHandler00);
   tolua_variable(tolua_S,"__CCTouchDelegate__",tolua_get_CCLayer___CCTouchDelegate__,NULL);
   tolua_variable(tolua_S,"__CCAccelerometerDelegate__",tolua_get_CCLayer___CCAccelerometerDelegate__,NULL);
   tolua_variable(tolua_S,"__CCKeypadDelegate__",tolua_get_CCLayer___CCKeypadDelegate__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCLayerMultiplex","CCLayerMultiplex","CCLayer",tolua_collect_CCLayerMultiplex);
  #else
  tolua_cclass(tolua_S,"CCLayerMultiplex","CCLayerMultiplex","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCLayerMultiplex");
   tolua_function(tolua_S,"createWithLayer",tolua_cocos2d_CCLayerMultiplex_createWithLayer00);
   tolua_function(tolua_S,"create",tolua_cocos2d_CCLayerMultiplex_create00);
   tolua_function(tolua_S,"getEnabledLayer",tolua_cocos2d_CCLayerMultiplex_getEnabledLayer00);
   tolua_function(tolua_S,"delete",tolua_cocos2d_CCLayerMultiplex_delete00);
   tolua_function(tolua_S,"new",tolua_cocos2d_CCLayerMultiplex_new00);
   tolua_function(tolua_S,"new_local",tolua_cocos2d_CCLayerMultiplex_new00_local);
   tolua_function(tolua_S,".call",tolua_cocos2d_CCLayerMultiplex_new00_local);
   tolua_function(tolua_S,"layerAt",tolua_cocos2d_CCLayerMultiplex_layerAt00);
   tolua_function(tolua_S,"addLayer",tolua_cocos2d_CCLayerMultiplex_addLayer00);
   tolua_function(tolua_S,"initWithLayers",tolua_cocos2d_CCLayerMultiplex_initWithLayers00);
   tolua_function(tolua_S,"switchTo",tolua_cocos2d_CCLayerMultiplex_switchTo00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCLayerGradient","CCLayerGradient","CCLayerColor",NULL);
  tolua_beginmodule(tolua_S,"CCLayerGradient");
   tolua_function(tolua_S,"create",tolua_cocos2d_CCLayerGradient_create00);
   tolua_function(tolua_S,"create",tolua_cocos2d_CCLayerGradient_create01);
   tolua_function(tolua_S,"getStartColor",tolua_cocos2d_CCLayerGradient_getStartColor00);
   tolua_function(tolua_S,"isCompressedInterpolation",tolua_cocos2d_CCLayerGradient_isCompressedInterpolation00);
   tolua_function(tolua_S,"getStartOpacity",tolua_cocos2d_CCLayerGradient_getStartOpacity00);
   tolua_function(tolua_S,"setStartOpacity",tolua_cocos2d_CCLayerGradient_setStartOpacity00);
   tolua_function(tolua_S,"setCompressedInterpolation",tolua_cocos2d_CCLayerGradient_setCompressedInterpolation00);
   tolua_function(tolua_S,"setEndOpacity",tolua_cocos2d_CCLayerGradient_setEndOpacity00);
   tolua_function(tolua_S,"init",tolua_cocos2d_CCLayerGradient_init00);
   tolua_function(tolua_S,"setEndColor",tolua_cocos2d_CCLayerGradient_setEndColor00);
   tolua_function(tolua_S,"initWithColor",tolua_cocos2d_CCLayerGradient_initWithColor00);
   tolua_function(tolua_S,"getEndColor",tolua_cocos2d_CCLayerGradient_getEndColor00);
   tolua_function(tolua_S,"getEndOpacity",tolua_cocos2d_CCLayerGradient_getEndOpacity00);
   tolua_function(tolua_S,"setStartColor",tolua_cocos2d_CCLayerGradient_setStartColor00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCLayerRGBA","CCLayerRGBA","CCLayer",tolua_collect_CCLayerRGBA);
  #else
  tolua_cclass(tolua_S,"CCLayerRGBA","CCLayerRGBA","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCLayerRGBA");
   tolua_function(tolua_S,"create",tolua_cocos2d_CCLayerRGBA_create00);
   tolua_function(tolua_S,"updateDisplayedColor",tolua_cocos2d_CCLayerRGBA_updateDisplayedColor00);
   tolua_function(tolua_S,"setColor",tolua_cocos2d_CCLayerRGBA_setColor00);
   tolua_function(tolua_S,"isCascadeOpacityEnabled",tolua_cocos2d_CCLayerRGBA_isCascadeOpacityEnabled00);
   tolua_function(tolua_S,"getColor",tolua_cocos2d_CCLayerRGBA_getColor00);
   tolua_function(tolua_S,"getDisplayedOpacity",tolua_cocos2d_CCLayerRGBA_getDisplayedOpacity00);
   tolua_function(tolua_S,"setCascadeColorEnabled",tolua_cocos2d_CCLayerRGBA_setCascadeColorEnabled00);
   tolua_function(tolua_S,"setOpacity",tolua_cocos2d_CCLayerRGBA_setOpacity00);
   tolua_function(tolua_S,"delete",tolua_cocos2d_CCLayerRGBA_delete00);
   tolua_function(tolua_S,"setCascadeOpacityEnabled",tolua_cocos2d_CCLayerRGBA_setCascadeOpacityEnabled00);
   tolua_function(tolua_S,"updateDisplayedOpacity",tolua_cocos2d_CCLayerRGBA_updateDisplayedOpacity00);
   tolua_function(tolua_S,"init",tolua_cocos2d_CCLayerRGBA_init00);
   tolua_function(tolua_S,"new",tolua_cocos2d_CCLayerRGBA_new00);
   tolua_function(tolua_S,"new_local",tolua_cocos2d_CCLayerRGBA_new00_local);
   tolua_function(tolua_S,".call",tolua_cocos2d_CCLayerRGBA_new00_local);
   tolua_function(tolua_S,"setOpacityModifyRGB",tolua_cocos2d_CCLayerRGBA_setOpacityModifyRGB00);
   tolua_function(tolua_S,"getOpacity",tolua_cocos2d_CCLayerRGBA_getOpacity00);
   tolua_function(tolua_S,"isOpacityModifyRGB",tolua_cocos2d_CCLayerRGBA_isOpacityModifyRGB00);
   tolua_function(tolua_S,"isCascadeColorEnabled",tolua_cocos2d_CCLayerRGBA_isCascadeColorEnabled00);
   tolua_function(tolua_S,"getDisplayedColor",tolua_cocos2d_CCLayerRGBA_getDisplayedColor00);
   tolua_variable(tolua_S,"__CCRGBAProtocol__",tolua_get_CCLayerRGBA___CCRGBAProtocol__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCLayerColor","CCLayerColor","CCLayerRGBA",tolua_collect_CCLayerColor);
  #else
  tolua_cclass(tolua_S,"CCLayerColor","CCLayerColor","CCLayerRGBA",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCLayerColor");
   tolua_function(tolua_S,"create",tolua_cocos2d_CCLayerColor_create00);
   tolua_function(tolua_S,"create",tolua_cocos2d_CCLayerColor_create01);
   tolua_function(tolua_S,"create",tolua_cocos2d_CCLayerColor_create02);
   tolua_function(tolua_S,"draw",tolua_cocos2d_CCLayerColor_draw00);
   tolua_function(tolua_S,"getBlendFunc",tolua_cocos2d_CCLayerColor_getBlendFunc00);
   tolua_function(tolua_S,"setColor",tolua_cocos2d_CCLayerColor_setColor00);
   tolua_function(tolua_S,"setBlendFunc",tolua_cocos2d_CCLayerColor_setBlendFunc00);
   tolua_function(tolua_S,"changeWidth",tolua_cocos2d_CCLayerColor_changeWidth00);
   tolua_function(tolua_S,"changeWidthAndHeight",tolua_cocos2d_CCLayerColor_changeWidthAndHeight00);
   tolua_function(tolua_S,"delete",tolua_cocos2d_CCLayerColor_delete00);
   tolua_function(tolua_S,"init",tolua_cocos2d_CCLayerColor_init00);
   tolua_function(tolua_S,"initWithColor",tolua_cocos2d_CCLayerColor_initWithColor00);
   tolua_function(tolua_S,"initWithColor",tolua_cocos2d_CCLayerColor_initWithColor01);
   tolua_function(tolua_S,"new",tolua_cocos2d_CCLayerColor_new00);
   tolua_function(tolua_S,"new_local",tolua_cocos2d_CCLayerColor_new00_local);
   tolua_function(tolua_S,".call",tolua_cocos2d_CCLayerColor_new00_local);
   tolua_function(tolua_S,"setOpacity",tolua_cocos2d_CCLayerColor_setOpacity00);
   tolua_function(tolua_S,"changeHeight",tolua_cocos2d_CCLayerColor_changeHeight00);
   tolua_variable(tolua_S,"__CCBlendProtocol__",tolua_get_CCLayerColor___CCBlendProtocol__,NULL);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"kValue100",kValue100);
  tolua_constant(tolua_S,"kCCTouchesAllAtOnce",kCCTouchesAllAtOnce);
  tolua_constant(tolua_S,"kCCTouchesOneByOne",kCCTouchesOneByOne);
  tolua_cclass(tolua_S,"someStruct2","someStruct2","",NULL);
  tolua_beginmodule(tolua_S,"someStruct2");
   tolua_variable(tolua_S,"i",tolua_get_someStruct2_i,tolua_set_someStruct2_i);
   tolua_variable(tolua_S,"f",tolua_get_someStruct2_f,tolua_set_someStruct2_f);
   tolua_variable(tolua_S,"d",tolua_get_someStruct2_d,tolua_set_someStruct2_d);
   tolua_variable(tolua_S,"n",tolua_get_someStruct2_n_ptr,tolua_set_someStruct2_n_ptr);
   tolua_function(tolua_S,"test",tolua_cocos2d_someStruct2_test00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ccColor4B","ccColor4B","",NULL);
  tolua_beginmodule(tolua_S,"ccColor4B");
   tolua_variable(tolua_S,"r",tolua_get_ccColor4B_r,tolua_set_ccColor4B_r);
   tolua_variable(tolua_S,"g",tolua_get_ccColor4B_g,tolua_set_ccColor4B_g);
   tolua_variable(tolua_S,"b",tolua_get_ccColor4B_b,tolua_set_ccColor4B_b);
   tolua_variable(tolua_S,"a",tolua_get_ccColor4B_a,tolua_set_ccColor4B_a);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ccBlendFunc","ccBlendFunc","",tolua_collect_ccBlendFunc);
  #else
  tolua_cclass(tolua_S,"ccBlendFunc","ccBlendFunc","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ccBlendFunc");
   tolua_variable(tolua_S,"src",tolua_get_ccBlendFunc_src,tolua_set_ccBlendFunc_src);
   tolua_variable(tolua_S,"dst",tolua_get_ccBlendFunc_dst,tolua_set_ccBlendFunc_dst);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"someStruct1","someStruct1","",NULL);
  tolua_beginmodule(tolua_S,"someStruct1");
   tolua_variable(tolua_S,"n",tolua_get_someStruct1_n_ptr,tolua_set_someStruct1_n_ptr);
   tolua_function(tolua_S,"test",tolua_cocos2d_someStruct1_test00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ccColor3B","ccColor3B","",NULL);
  tolua_beginmodule(tolua_S,"ccColor3B");
   tolua_variable(tolua_S,"r",tolua_get_ccColor3B_r,tolua_set_ccColor3B_r);
   tolua_variable(tolua_S,"g",tolua_get_ccColor3B_g,tolua_set_ccColor3B_g);
   tolua_variable(tolua_S,"b",tolua_get_ccColor3B_b,tolua_set_ccColor3B_b);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_cocos2d (lua_State* tolua_S) {
 return tolua_cocos2d_open(tolua_S);
};
#endif

