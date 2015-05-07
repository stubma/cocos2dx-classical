#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/android/jni/JniHelper.h"
#include "cocos2d.h"
#include <jni.h>
#include <android/log.h>
#include "CCApplicationLua.h"

using namespace cocos2d;

#ifdef __cplusplus
extern "C" {
#endif

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JniHelper::setJavaVM(vm);
    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h) {
    if(!CCDirector::sharedDirector()->getOpenGLView()) {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);
        CCApplicationLua* app = new CCApplicationLua(CCUtils::getExternalOrFullPath("script/main.lua"));
        CCApplication::sharedApplication()->run();
    } else {
        ccDrawInit();
        ccGLInvalidateStateCache();
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVENT_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

#ifdef __cplusplus
}
#endif

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
