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
LOCAL_MODULE := hellolua
LOCAL_SRC_FILES := $(call all-cpp-files-under,.)
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static \
	cocos_extension_static
include $(BUILD_SHARED_LIBRARY)
$(call import-module,cocos2dx)
$(call import-module,extensions)
