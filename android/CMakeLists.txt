cmake_minimum_required(VERSION 3.4.1)
project(VisionCameraFaceDetector)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 17)

# Add the raylib sources
add_library(raylib SHARED
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rcore.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rmodels.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rshapes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rtext.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/rtextures.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/raudio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/utils.c
)

include_directories(
  ${ANDROID_NDK}/sources/android/native_app_glue/
  ${CMAKE_CURRENT_SOURCE_DIR}/../externals/raylib/src/
  )

  # Define compiler macros for raylib
target_compile_definitions(raylib PRIVATE
                GRAPHICS_API_OPENGL_ES2
                PLATFORM_ANDROID
                __ANDROID__
)

# Link required libraries to raylib
target_link_libraries(raylib log android EGL GLESv2 OpenSLES dl m c)

# Add specific compilation options based on target Android architecture
if(CMAKE_ANDROID_ARCH_ABI STREQUAL "armeabi-v7a")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfloat-abi=softfp -mfpu=vfpv3-d16")
elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfix-cortex-a53-835769")
endif()



add_library(react-native-vision-camera-face-detector            SHARED
            ../cpp/react-native-vision-camera-face-detector.cpp
            cpp-adapter.cpp
)



# Specifies a path to native header files.
include_directories(
            ../cpp
)
