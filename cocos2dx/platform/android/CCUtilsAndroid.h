#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "ccTypes.h"
#include "CCUtils.h"
#include <jni.h>

NS_CC_BEGIN

class CCUtilsAndroid : public CCUtils {
public:
    /// get JNIEnv
    static JNIEnv* getJNIEnv();

    /// get context
    static jobject getContext();

    // for activity starting
    static jobject newIntent(const char* activityName);
    static jobject newIntentByAction(const char* action);
    static void setIntentUri(jobject intent, const char* uri);
    static void putBooleanExtra(jobject intent, const char* name, bool value);
    static void putByteExtra(jobject intent, const char* name, unsigned char value);
    static void putCharExtra(jobject intent, const char* name, unsigned short value);
    static void putDoubleExtra(jobject intent, const char* name, double value);
    static void putFloatExtra(jobject intent, const char* name, float value);
    static void putIntExtra(jobject intent, const char* name, int value);
    static void putStringExtra(jobject intent, const char* name, const char* value);
    static void putLongExtra(jobject intent, const char* name, long value);
    static void putShortExtra(jobject intent, const char* name, short value);
    static void putParcelableExtra(jobject intent, const char* name, jobject value);
    static void startActivity(jobject intent);
    static void sendBroadcast(jobject intent);
};

NS_CC_END

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID