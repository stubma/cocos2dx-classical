LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_sqlite3_static
LOCAL_MODULE_FILENAME := sqlite
LOCAL_SRC_FILES := libraries/$(TARGET_ARCH_ABI)/libsqlite.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_STATIC_LIBRARY)
