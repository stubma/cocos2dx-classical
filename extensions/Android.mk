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

# module
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := cocos_extension_static
LOCAL_MODULE_FILENAME := libextension
LOCAL_SRC_FILES := $(call all-cpp-files-under,.)
LOCAL_CFLAGS += -fexceptions -Qunused-arguments
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
	$(LOCAL_PATH)/GUI/CCControlExtension \
	$(LOCAL_PATH)/GUI/CCScrollView \
	$(LOCAL_PATH)/CocoStudio/Armature \
    $(LOCAL_PATH)/CocoStudio/Armature/utils
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static \
	cocosdenshion_static \
	box2d_static \
	chipmunk_static \
	cocos_lua_static
include $(BUILD_STATIC_LIBRARY)
$(call import-module,cocos2dx)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,scripting/lua)