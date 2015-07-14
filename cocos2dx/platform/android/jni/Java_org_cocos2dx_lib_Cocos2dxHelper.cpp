#include <stdlib.h>
#include <jni.h>
#include <android/log.h>
#include <string>
#include "JniHelper.h"
#include "cocoa/CCString.h"
#include "cocoa/CCGeometry.h"
#include "support/utils/CCUtils.h"
#include "CCEGLView.h"
#include "Java_org_cocos2dx_lib_Cocos2dxHelper.h"


#define  LOG_TAG    "Java_org_cocos2dx_lib_Cocos2dxHelper.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  CLASS_NAME "org/cocos2dx/lib/Cocos2dxHelper"

static EditTextCallback s_pfEditTextCallback = NULL;
static void* s_ctx = NULL;

using namespace cocos2d;
using namespace std;

string g_apkPath;

extern "C" {

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetApkPath(JNIEnv*  env, jclass clazz, jstring apkPath) {
        g_apkPath = JniHelper::jstring2string(apkPath);
    }

    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeSetEditTextDialogResult(JNIEnv * env, jclass clazz, jbyteArray text) {
        jsize  size = env->GetArrayLength(text);

        if (size > 0) {
            jbyte * data = (jbyte*)env->GetByteArrayElements(text, 0);
            char* pBuf = (char*)malloc(size+1);
            if (pBuf != NULL) {
                memcpy(pBuf, data, size);
                pBuf[size] = '\0';
                // pass data to edittext's delegate
                if (s_pfEditTextCallback) s_pfEditTextCallback(pBuf, s_ctx);
                free(pBuf);
            }
            env->ReleaseByteArrayElements(text, data, 0);
        } else {
            if (s_pfEditTextCallback) s_pfEditTextCallback("", s_ctx);
        }
    }

    JNIEXPORT jstring JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeFullPathForFilename(JNIEnv* env, jclass clazz, jstring filename) {
        string fn = JniHelper::jstring2string(filename);
        string path = CCUtils::getExternalOrFullPath(fn);
        return env->NewStringUTF(path.c_str());
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_Cocos2dxHelper_nativeGetViewPortRect(JNIEnv* env, jclass clazz, jobject r) {
        // get rect
        const CCRect& rect = CCEGLView::sharedOpenGLView()->getViewPortRect();
        
        // Rect class
        jclass klass = env->GetObjectClass(r);
        jfieldID fid_bottom = env->GetFieldID(klass, "bottom", "I");
        jfieldID fid_left = env->GetFieldID(klass, "left", "I");
        jfieldID fid_right = env->GetFieldID(klass, "right", "I");
        jfieldID fid_top = env->GetFieldID(klass, "top", "I");
        
        // set it
        env->SetIntField(r, fid_left, rect.origin.x);
        env->SetIntField(r, fid_bottom, rect.origin.y);
        env->SetIntField(r, fid_right, rect.origin.x + rect.size.width);
        env->SetIntField(r, fid_top, rect.origin.y + rect.size.height);
        
        // release
        env->DeleteLocalRef(klass);
    }
}

const char * getApkPath() {
    return g_apkPath.c_str();
}

void showDialogJNI(const char * pszMsg, const char * pszTitle) {
    if (!pszMsg) {
        return;
    }

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showDialog", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1;

        if (!pszTitle) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(pszTitle);
        }

        jstring stringArg2 = t.env->NewStringUTF(pszMsg);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void showEditTextDialogJNI(const char* pszTitle, const char* pszMessage, int nInputMode, int nInputFlag, int nReturnType, int nMaxLength, EditTextCallback pfEditTextCallback, void* ctx) {
    if (pszMessage == NULL) {
        return;
    }

    s_pfEditTextCallback = pfEditTextCallback;
    s_ctx = ctx;

    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showEditTextDialog", "(Ljava/lang/String;Ljava/lang/String;IIII)V")) {
        jstring stringArg1;

        if (!pszTitle) {
            stringArg1 = t.env->NewStringUTF("");
        } else {
            stringArg1 = t.env->NewStringUTF(pszTitle);
        }

        jstring stringArg2 = t.env->NewStringUTF(pszMessage);

        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2, nInputMode, nInputFlag, nReturnType, nMaxLength);

        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void terminateProcessJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "terminateProcess", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

std::string getPackageNameJNI() {
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxPackageName", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    return ret;
}

std::string getFileDirectoryJNI() {
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCocos2dxWritablePath", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }
    
    return ret;
}

std::string getCurrentLanguageJNI() {
    JniMethodInfo t;
    std::string ret("");
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getCurrentLanguage", "()Ljava/lang/String;")) {
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        ret = JniHelper::jstring2string(str);
        t.env->DeleteLocalRef(str);
    }

    return ret;
}

void enableAccelerometerJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "enableAccelerometer", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void setAccelerometerIntervalJNI(float interval) {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setAccelerometerInterval", "(F)V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, interval);
        t.env->DeleteLocalRef(t.classID);
    }
}

void disableAccelerometerJNI() {
    JniMethodInfo t;

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "disableAccelerometer", "()V")) {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

// functions for CCUserDefault
bool getBoolForKeyJNI(const char* pKey, bool defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getBoolForKey", "(Ljava/lang/String;Z)Z")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

int getIntegerForKeyJNI(const char* pKey, int defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getIntegerForKey", "(Ljava/lang/String;I)I")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

float getFloatForKeyJNI(const char* pKey, float defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getFloatForKey", "(Ljava/lang/String;F)F")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jfloat ret = t.env->CallStaticFloatMethod(t.classID, t.methodID, stringArg, defaultValue);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

double getDoubleForKeyJNI(const char* pKey, double defaultValue)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getDoubleForKey", "(Ljava/lang/String;D)D")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        jdouble ret = t.env->CallStaticDoubleMethod(t.classID, t.methodID, stringArg);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
        
        return ret;
    }
    
    return defaultValue;
}

std::string getStringForKeyJNI(const char* pKey, const char* defaultValue)
{
    JniMethodInfo t;
    std::string ret("");

    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getStringForKey", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
        jstring stringArg1 = t.env->NewStringUTF(pKey);
        jstring stringArg2 = t.env->NewStringUTF(defaultValue);
        jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, stringArg1, stringArg2);
        ret = JniHelper::jstring2string(str);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
        t.env->DeleteLocalRef(str);
        
        return ret;
    }
    
    return defaultValue;
}

void setBoolForKeyJNI(const char* pKey, bool value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setBoolForKey", "(Ljava/lang/String;Z)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setIntegerForKeyJNI(const char* pKey, int value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setIntegerForKey", "(Ljava/lang/String;I)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setFloatForKeyJNI(const char* pKey, float value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setFloatForKey", "(Ljava/lang/String;F)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setDoubleForKeyJNI(const char* pKey, double value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setDoubleForKey", "(Ljava/lang/String;D)V")) {
        jstring stringArg = t.env->NewStringUTF(pKey);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg, value);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg);
    }
}

void setStringForKeyJNI(const char* pKey, const char* value)
{
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setStringForKey", "(Ljava/lang/String;Ljava/lang/String;)V")) {
        jstring stringArg1 = t.env->NewStringUTF(pKey);
        jstring stringArg2 = t.env->NewStringUTF(value);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
        t.env->DeleteLocalRef(stringArg2);
    }
}