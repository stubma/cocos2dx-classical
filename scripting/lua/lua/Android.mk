LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := lua_static
LOCAL_MODULE_FILENAME := liblua
LOCAL_SRC_FILES := ./prebuilt/android/$(TARGET_ARCH_ABI)/liblua.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/src/src
include $(PREBUILT_STATIC_LIBRARY)
