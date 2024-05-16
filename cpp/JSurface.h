//
// Created by rodrigo gomes on 16/05/24.
//

#pragma once

#include <fbjni/fbjni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

namespace FaceDetector {
    using namespace facebook::jni;

    class JSurface : public JavaClass<JSurface> {
    public:
        static constexpr auto kJavaDescriptor = "Landroid/view/Surface;";
    };
}
