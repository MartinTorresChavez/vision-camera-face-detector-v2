//
// Created by rodrigo gomes on 16/05/24.
//

#pragma once

#include <fbjni/fbjni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

namespace FaceDetector {

    class JContext : public facebook::jni::JavaClass<JContext> {
    public:
        static constexpr auto kJavaDescriptor = "Landroid/content/Context;";
    };

    class JSurface : public facebook::jni::JavaClass<JSurface> {
    public:
        static constexpr auto kJavaDescriptor = "Landroid/view/Surface;";

        ANativeWindow* getNativeWindow() const;
    };

    class JSurfaceHolder : public facebook::jni::JavaClass<JSurfaceHolder> {
    public:
        static constexpr auto kJavaDescriptor = "Landroid/view/SurfaceHolder;";

        facebook::jni::local_ref<JSurface> getSurface() const;
    };

}
