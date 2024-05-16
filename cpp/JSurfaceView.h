//
// Created by rodrigo gomes on 16/05/24.
//

#pragma once

#include <fbjni/fbjni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

namespace FaceDetector {
    using namespace facebook::jni;

    class JSurfaceHolder;

    class JSurfaceView : public JavaClass<JSurfaceView> {
    public:
        static constexpr auto kJavaDescriptor = "Landroid/view/SurfaceView;";

        static local_ref<JSurfaceView> create(alias_ref<JObject> context);


        local_ref<JSurfaceHolder> getHolder() const;
    };

}
