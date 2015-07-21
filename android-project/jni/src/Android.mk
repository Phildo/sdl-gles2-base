LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SDL_IMG_PATH := ../SDL_image

CPP_FILES := $(subst $(LOCAL_PATH)/,,$(wildcard $(LOCAL_PATH)/src/*.cpp))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/$(SDL_IMG_PATH)

LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c $(CPP_FILES)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)

