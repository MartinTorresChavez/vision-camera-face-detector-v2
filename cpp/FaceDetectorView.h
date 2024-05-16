//
// Created by rodrigo gomes on 15/05/24.
//

#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

namespace FaceDetector {
    using namespace facebook;
    using namespace facebook::jni;

    class FaceDetectorView : public HybridClass<FaceDetectorView> {
    public:
        ~FaceDetectorView();
        static void registerNatives();
        jsi::Runtime *getJSRuntime();
        ANativeWindow* getNativeWindow();


    private:
        friend HybridBase;
        jni::global_ref<FaceDetectorView::javaobject> _javaPart;
        jsi::Runtime *_runtime;
        ANativeWindow* _nativeWindow;


        static auto constexpr TAG = "FaceDetectorView";
        static auto constexpr kJavaDescriptor = "Lcom/visioncamerafacedetector/FaceDetectorView;";

        explicit FaceDetectorView(const alias_ref<FaceDetectorView::jhybridobject> &javaThis,
                                  jsi::Runtime *jsRuntime, alias_ref<JObject> context);

        static jni::local_ref<jhybriddata>
        initHybrid(jni::alias_ref<jhybridobject> javaThis, jlong jsRuntimePointer, alias_ref<JObject> context);
    };

}
