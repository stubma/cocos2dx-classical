# macros to include all files with same extension
define all-files-under
$(patsubst ./%,%, \
  $(shell cd $(LOCAL_PATH) ; \
          find $(1) -name "$(2)" -and -not -name ".*") \
 )
endef

define all-cpp-files-under
$(call all-files-under,$(1),*.cpp)
endef

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocosdenshion_static
LOCAL_MODULE_FILENAME := libcocosdenshion
LOCAL_SRC_FILES := $(call all-cpp-files-under,.)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include \
    $(LOCAL_PATH)/../../cocos2dx \
    $(LOCAL_PATH)/../../cocos2dx/include \
    $(LOCAL_PATH)/../../cocos2dx/kazmath/include \
    $(LOCAL_PATH)/../../cocos2dx/platform/android \
    $(LOCAL_PATH)/../../cocos2dx/platform/android/jni
include $(BUILD_STATIC_LIBRARY)
