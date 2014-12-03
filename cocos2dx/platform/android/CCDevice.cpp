#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "platform/CCDevice.h"
#include "jni/DPIJni.h"

NS_CC_BEGIN

int CCDevice::getDPI()
{
    static int dpi = -1;
    if (dpi == -1)
    {
        dpi = (int)getDPIJNI();
    }
    return dpi;
}

NS_CC_END

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID