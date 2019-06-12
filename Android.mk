LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main
LOCAL_C_INCLUDES += \
        /gpio/

LOCAL_SRC_FILES := main.cpp gpio/GPIOClass.cpp

# LOCAL_LDLIBS := -lfoo -lbar # replace lib by -1


include $(BUILD_EXECUTABLE)
