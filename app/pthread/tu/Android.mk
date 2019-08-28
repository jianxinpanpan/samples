LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= main.c

LOCAL_SHARED_LIBRARIES := \
	libcutils 


LOCAL_MODULE:= boost_antutu


include $(BUILD_EXECUTABLE)
