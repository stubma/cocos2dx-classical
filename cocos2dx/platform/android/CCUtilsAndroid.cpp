//
//  CCUtilsAndroid.h
//  cocos2dx
//
//  Created by maruojie on 14/11/27.
//  Copyright (c) 2014年 cocos2d-x. All rights reserved.
//

#include "CCUtilsAndroid.h"
#include "ccTypes.h"
#include "CCUtils.h"
#include <jni.h>

NS_CC_BEGIN

JNIEnv* CCUtilsAndroid::getJNIEnv() {
    JavaVM* vm = JniHelper::getJavaVM();
    JNIEnv* env = NULL;
    if(vm) {
        jint ret = vm->GetEnv((void**) &env, JNI_VERSION_1_4);
        if (ret != JNI_OK) {
            jint status = vm->AttachCurrentThread(&env, NULL);
            if(status < 0) {
                CCLOGERROR("getJNIEnv: failed to attach current thread");
                env = NULL;
            }
        }
    }
    
    return env;
}

jobject CCUtilsAndroid::getContext() {
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;");
    jobject ctx = t.env->CallStaticObjectMethod(t.classID, t.methodID);
    return ctx;
}

jobject CCUtilsAndroid::newIntent(const char* activityName) {
    // get context
    jobject context = getContext();
    
    // find constructor
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "<init>", "(Landroid/content/Context;Ljava/lang/Class;)V");
    
    // create activity name
    size_t len = strlen(activityName);
    char* jniName = (char*)calloc(len + 1, sizeof(char));
    for(int i = 0; i < len; i++) {
        if(activityName[i] == '.')
            jniName[i] = '/';
        else
            jniName[i] = activityName[i];
    }
    jclass actClass = t.env->FindClass(jniName);
    
    // new intent
    jobject intent = t.env->NewObject(t.classID, t.methodID, context, actClass);
    
    // clear
    t.env->DeleteLocalRef(actClass);
    t.env->DeleteLocalRef(context);
    CC_SAFE_FREE(jniName);
    
    return intent;
}

jobject CCUtilsAndroid::newIntentByAction(const char* action) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "<init>", "(Ljava/lang/String;)V");
    jstring a = t.env->NewStringUTF(action);
    jobject intent = t.env->NewObject(t.classID, t.methodID, a);
    t.env->DeleteLocalRef(a);
    return intent;
}

void CCUtilsAndroid::setIntentUri(jobject intent, const char* uri) {
    JniMethodInfo t;
    JniHelper::getStaticMethodInfo(t, "android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
    jstring jUriStr = t.env->NewStringUTF(uri);
    jobject jUri = t.env->CallStaticObjectMethod(t.classID, t.methodID, jUriStr);
    JniHelper::getMethodInfo(t, "android/content/Intent", "setData", "(Landroid/net/Uri;)Landroid/content/Intent;");
    t.env->CallObjectMethod(intent, t.methodID, jUri);
    t.env->DeleteLocalRef(jUri);
    t.env->DeleteLocalRef(jUriStr);
}

void CCUtilsAndroid::putBooleanExtra(jobject intent, const char* name, bool value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;Z)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putByteExtra(jobject intent, const char* name, unsigned char value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;B)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putCharExtra(jobject intent, const char* name, unsigned short value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;C)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putDoubleExtra(jobject intent, const char* name, double value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;D)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putFloatExtra(jobject intent, const char* name, float value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;F)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putIntExtra(jobject intent, const char* name, int value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;I)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putStringExtra(jobject intent, const char* name, const char* value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putLongExtra(jobject intent, const char* name, long value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;J)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putShortExtra(jobject intent, const char* name, short value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;S)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::putParcelableExtra(jobject intent, const char* name, jobject value) {
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Intent", "putExtra", "(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;");
    jstring s = t.env->NewStringUTF(name);
    t.env->CallObjectMethod(intent, t.methodID, s, value);
    t.env->DeleteLocalRef(s);
}

void CCUtilsAndroid::startActivity(jobject intent) {
    jobject ctx = getContext();
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Context", "startActivity", "(Landroid/content/Intent;)V");
    t.env->CallVoidMethod(ctx, t.methodID, intent);
    t.env->DeleteLocalRef(ctx);
}

void CCUtilsAndroid::sendBroadcast(jobject intent) {
    jobject ctx = getContext();
    JniMethodInfo t;
    JniHelper::getMethodInfo(t, "android/content/Context", "sendBroadcast", "(Landroid/content/Intent;)V");
    t.env->CallVoidMethod(ctx, t.methodID, intent);
    t.env->DeleteLocalRef(ctx);
}

NS_CC_END