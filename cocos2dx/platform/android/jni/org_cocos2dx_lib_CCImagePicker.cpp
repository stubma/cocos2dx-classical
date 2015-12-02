/****************************************************************************
 Author: Luma (stubma@gmail.com)

 https://github.com/stubma/cocos2dx-classical

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <jni.h>
#include "ccTypes.h"
#include "platform/android/jni/JniHelper.h"
#include "CCImagePicker.h"
#include "CCImagePickerCallback.h"
#include "CCScheduler.h"
#include "CCDirector.h"

USING_NS_CC;
using namespace std;

/**
 * XXX: If we directly callback when image picker is done, the texture won't be created.
 * I can't figure out why, maybe the surface is not running so texture loading is failed.
 * This is a workaround for this issue, I delay the callback until game re-gains the
 * control. However, I have to define a stub CCObject to provide a schedule selector.
 */
class DelayCallback : public CCObject {
private:
	bool m_cancelled;
    CCImagePicker* m_picker;

public:
	DelayCallback(CCImagePicker* picker, bool cancelled = false) :
		m_cancelled(cancelled),
		m_picker(picker) {
		// set a very small delay so that it will be called next frame
		CCScheduler* s = CCDirector::sharedDirector()->getScheduler();
		s->scheduleSelector(schedule_selector(DelayCallback::delayCallback), this, 0, 0, 0.001f, false);
	}

	virtual ~DelayCallback() {}

	void delayCallback(float delta) {
		if(m_cancelled) {
            m_picker->notifyImagePickingCancelled();
		} else {
            m_picker->notifyImagePickedOK();
		}

		// release self
		autorelease();
	}
};

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCImagePicker_nativeSetFullPath
(JNIEnv * env, jclass clazz, jlong picker, jstring fullPath) {
    CCImagePicker* ccPicker = (CCImagePicker*)picker;
    ccPicker->setFullPath(JniHelper::jstring2string(fullPath));
}
    
JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCImagePicker_nativeOnImagePicked
  (JNIEnv * env, jclass clazz, jlong picker) {
	CCImagePicker* ccPicker = (CCImagePicker*)picker;
	if(ccPicker) {
		new DelayCallback(ccPicker);
	}
}

JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCImagePicker_nativeOnImagePickingCancelled
  (JNIEnv * env, jclass clazz, jlong picker) {
	CCImagePicker* ccPicker = (CCImagePicker*)picker;
	if(ccPicker) {
		new DelayCallback(ccPicker, true);
	}
}

#ifdef __cplusplus
}
#endif

#endif // #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID