#ifndef __CCDEVICE_H__
#define __CCDEVICE_H__

#include "CCPlatformMacros.h"

NS_CC_BEGIN
/**
 @js NA
 @lua NA
 */
class CC_DLL CCDevice
{
private:
    CCDevice();
public:
    /**
     *  Gets the DPI of device
     *  @return The DPI of device.
     */
    static int getDPI();
    
    /// get platform constants
    /// lua can query constants defined Cocos2dCosntants.lua
    static int getPlatform() {
        return CC_TARGET_PLATFORM;
    }
};


NS_CC_END

#endif /* __CCDEVICE_H__ */
