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

define all-c-files-under
$(call all-files-under,$(1),*.c)
endef

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := cocos_lua_static
LOCAL_MODULE_FILENAME := liblua
LOCAL_SRC_FILES := $(call all-cpp-files-under,cocos2dx_support) \
	$(call all-c-files-under,cocos2dx_support) \
	$(call all-c-files-under,tolua)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/cocos2dx_support \
	$(LOCAL_PATH)/tolua \
	$(LOCAL_PATH)/luajit/src/src
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_WHOLE_STATIC_LIBRARIES := luajit_static \
	cocos2dx_static \
	cocosdenshion_static \
	cocos_extension_static
include $(BUILD_STATIC_LIBRARY)
$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,scripting/lua/luajit)
