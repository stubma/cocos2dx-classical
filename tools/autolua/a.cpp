/*
** Lua binding: SimpleNativeClass
** Generated automatically by tolua++-1.0.92 on Sat Dec 27 16:12:11 2014.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_SimpleNativeClass_open (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SimpleNativeClass (lua_State* tolua_S)
{
 SimpleNativeClass* self = (SimpleNativeClass*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SimpleNativeClass");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"cocos2d::CCNode");
}

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
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_create00
static int tolua_SimpleNativeClass_SimpleNativeClass_create00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_func00
static int tolua_SimpleNativeClass_SimpleNativeClass_func00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_func01
static int tolua_SimpleNativeClass_SimpleNativeClass_func01(lua_State* tolua_S)
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
 return tolua_SimpleNativeClass_SimpleNativeClass_func00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnotherMoreComplexField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_getAnotherMoreComplexField00
static int tolua_SimpleNativeClass_SimpleNativeClass_getAnotherMoreComplexField00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_setSomeField00
static int tolua_SimpleNativeClass_SimpleNativeClass_setSomeField00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SimpleNativeClass",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const cocos2d::CCNode",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"const cocos2d::CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SimpleNativeClass* self = (SimpleNativeClass*)  tolua_tousertype(tolua_S,1,0);
  const cocos2d::CCNode* n = ((const cocos2d::CCNode*)  tolua_tousertype(tolua_S,2,0));
  const cocos2d::CCNode* pn = ((const cocos2d::CCNode*)  tolua_tousertype(tolua_S,3,0));
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
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_setSomeField01
static int tolua_SimpleNativeClass_SimpleNativeClass_setSomeField01(lua_State* tolua_S)
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
 return tolua_SimpleNativeClass_SimpleNativeClass_setSomeField00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAge of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_getAge00
static int tolua_SimpleNativeClass_SimpleNativeClass_getAge00(lua_State* tolua_S)
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

/* method: thisReturnsALongLong of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_thisReturnsALongLong00
static int tolua_SimpleNativeClass_SimpleNativeClass_thisReturnsALongLong00(lua_State* tolua_S)
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

/* method: getObjectType of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_getObjectType00
static int tolua_SimpleNativeClass_SimpleNativeClass_getObjectType00(lua_State* tolua_S)
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
   unsigned int tolua_ret = (unsigned int)  self->getObjectType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: setAnotherMoreComplexField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_setAnotherMoreComplexField00
static int tolua_SimpleNativeClass_SimpleNativeClass_setAnotherMoreComplexField00(lua_State* tolua_S)
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

/* method: setSomeOtherField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_setSomeOtherField00
static int tolua_SimpleNativeClass_SimpleNativeClass_setSomeOtherField00(lua_State* tolua_S)
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

/* method: setAge of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_setAge00
static int tolua_SimpleNativeClass_SimpleNativeClass_setAge00(lua_State* tolua_S)
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

/* method: delete of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_delete00
static int tolua_SimpleNativeClass_SimpleNativeClass_delete00(lua_State* tolua_S)
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

/* method: init of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_init00
static int tolua_SimpleNativeClass_SimpleNativeClass_init00(lua_State* tolua_S)
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

/* method: new of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_new00
static int tolua_SimpleNativeClass_SimpleNativeClass_new00(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_new00_local
static int tolua_SimpleNativeClass_SimpleNativeClass_new00_local(lua_State* tolua_S)
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
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_new01
static int tolua_SimpleNativeClass_SimpleNativeClass_new01(lua_State* tolua_S)
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
 return tolua_SimpleNativeClass_SimpleNativeClass_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_new01_local
static int tolua_SimpleNativeClass_SimpleNativeClass_new01_local(lua_State* tolua_S)
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
 return tolua_SimpleNativeClass_SimpleNativeClass_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_new02
static int tolua_SimpleNativeClass_SimpleNativeClass_new02(lua_State* tolua_S)
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
 return tolua_SimpleNativeClass_SimpleNativeClass_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_new02_local
static int tolua_SimpleNativeClass_SimpleNativeClass_new02_local(lua_State* tolua_S)
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
 return tolua_SimpleNativeClass_SimpleNativeClass_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSomeOtherField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_getSomeOtherField00
static int tolua_SimpleNativeClass_SimpleNativeClass_getSomeOtherField00(lua_State* tolua_S)
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

/* method: getSomeField of class  SimpleNativeClass */
#ifndef TOLUA_DISABLE_tolua_SimpleNativeClass_SimpleNativeClass_getSomeField00
static int tolua_SimpleNativeClass_SimpleNativeClass_getSomeField00(lua_State* tolua_S)
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
  someThingEnumerated func = ((someThingEnumerated) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSomeField'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSomeField(func);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSomeField'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_SimpleNativeClass_open (lua_State* tolua_S)
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
   tolua_variable(tolua_S,"m_someOtherField",tolua_get_SimpleNativeClass_m_someOtherField,tolua_set_SimpleNativeClass_m_someOtherField);
   tolua_function(tolua_S,"create",tolua_SimpleNativeClass_SimpleNativeClass_create00);
   tolua_function(tolua_S,"func",tolua_SimpleNativeClass_SimpleNativeClass_func00);
   tolua_function(tolua_S,"func",tolua_SimpleNativeClass_SimpleNativeClass_func01);
   tolua_function(tolua_S,"getAnotherMoreComplexField",tolua_SimpleNativeClass_SimpleNativeClass_getAnotherMoreComplexField00);
   tolua_function(tolua_S,"setSomeField",tolua_SimpleNativeClass_SimpleNativeClass_setSomeField00);
   tolua_function(tolua_S,"setSomeField",tolua_SimpleNativeClass_SimpleNativeClass_setSomeField01);
   tolua_function(tolua_S,"getAge",tolua_SimpleNativeClass_SimpleNativeClass_getAge00);
   tolua_function(tolua_S,"thisReturnsALongLong",tolua_SimpleNativeClass_SimpleNativeClass_thisReturnsALongLong00);
   tolua_function(tolua_S,"getObjectType",tolua_SimpleNativeClass_SimpleNativeClass_getObjectType00);
   tolua_function(tolua_S,"setAnotherMoreComplexField",tolua_SimpleNativeClass_SimpleNativeClass_setAnotherMoreComplexField00);
   tolua_function(tolua_S,"setSomeOtherField",tolua_SimpleNativeClass_SimpleNativeClass_setSomeOtherField00);
   tolua_function(tolua_S,"setAge",tolua_SimpleNativeClass_SimpleNativeClass_setAge00);
   tolua_function(tolua_S,"delete",tolua_SimpleNativeClass_SimpleNativeClass_delete00);
   tolua_function(tolua_S,"init",tolua_SimpleNativeClass_SimpleNativeClass_init00);
   tolua_function(tolua_S,"new",tolua_SimpleNativeClass_SimpleNativeClass_new00);
   tolua_function(tolua_S,"new_local",tolua_SimpleNativeClass_SimpleNativeClass_new00_local);
   tolua_function(tolua_S,".call",tolua_SimpleNativeClass_SimpleNativeClass_new00_local);
   tolua_function(tolua_S,"new",tolua_SimpleNativeClass_SimpleNativeClass_new01);
   tolua_function(tolua_S,"new_local",tolua_SimpleNativeClass_SimpleNativeClass_new01_local);
   tolua_function(tolua_S,".call",tolua_SimpleNativeClass_SimpleNativeClass_new01_local);
   tolua_function(tolua_S,"new",tolua_SimpleNativeClass_SimpleNativeClass_new02);
   tolua_function(tolua_S,"new_local",tolua_SimpleNativeClass_SimpleNativeClass_new02_local);
   tolua_function(tolua_S,".call",tolua_SimpleNativeClass_SimpleNativeClass_new02_local);
   tolua_function(tolua_S,"getSomeOtherField",tolua_SimpleNativeClass_SimpleNativeClass_getSomeOtherField00);
   tolua_function(tolua_S,"getSomeField",tolua_SimpleNativeClass_SimpleNativeClass_getSomeField00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"kValue1",kValue1);
  tolua_constant(tolua_S,"kValue2",kValue2);
  tolua_constant(tolua_S,"kValue3",kValue3);
  tolua_constant(tolua_S,"kValue4",kValue4);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_SimpleNativeClass (lua_State* tolua_S) {
 return tolua_SimpleNativeClass_open(tolua_S);
};
#endif

