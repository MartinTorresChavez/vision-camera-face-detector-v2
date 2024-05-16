cmake_minimum_required(VERSION 3.4.1)
project(VisionCameraFaceDetector)
set (PACKAGE_NAME "faceDetector")

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 20)

include_directories(
  ${ANDROID_NDK}/sources/android/native_app_glue/
  ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/
)

find_package(ReactAndroid REQUIRED CONFIG)
find_package(fbjni REQUIRED CONFIG)


add_library(raylib SHARED
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rcore.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rmodels.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rshapes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rtext.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rtextures.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/utils.c
)


# Define compiler macros for raylib
target_compile_definitions(raylib PRIVATE
                GRAPHICS_API_OPENGL_ES2
                PLATFORM_ANDROID
                __ANDROID__
)

target_link_libraries(raylib PRIVATE
    android
    log
    EGL
    GLESv2
    OpenSLES
    dl
    m
    c
)

# raylib: Add specific compilation options based on target Android architecture
if(CMAKE_ANDROID_ARCH_ABI STREQUAL "armeabi-v7a")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=softfp -mfpu=vfpv3-d16")
elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfix-cortex-a53-835769")
endif()


add_library(${PACKAGE_NAME}
            SHARED
            ../cpp/JniOnLoad.cpp
            ../cpp/FaceDetectorView.cpp
            ../cpp/JSurfaceView.cpp
            ../cpp/JSurfaceHolder.cpp
)

target_include_directories(
        ${PACKAGE_NAME}
        PUBLIC
        "${NODE_MODULES_DIR}/react-native/ReactCommon"
        "${NODE_MODULES_DIR}/react-native/ReactCommon/callinvoker"
        "${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/jni/react/turbomodule"
)

target_link_libraries(
          ${PACKAGE_NAME}
          android
          log
          raylib
          ReactAndroid::jsi
          ReactAndroid::reactnativejni
          fbjni::fbjni
)
