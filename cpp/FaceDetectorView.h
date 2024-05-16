#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <fbjni/detail/CoreClasses.h>

#include "JSurface.h"

namespace FaceDetector {
    using namespace facebook::jni;
    using namespace facebook::jsi;

    class FaceDetectorView : public HybridClass<FaceDetectorView> {
    public:
        static constexpr auto kJavaDescriptor = "Lcom/visioncamerafacedetector/FaceDetectorView;";

        static void registerNatives();

        FaceDetectorView(const alias_ref<FaceDetectorView::jhybridobject> &javaThis,
                         Runtime *runtime, alias_ref<JObject> context);

        ~FaceDetectorView();

        Runtime *getJSRuntime();
        ANativeWindow* getNativeWindow();

    private:
        static local_ref<HybridClass<FaceDetectorView>::jhybriddata> initHybrid(alias_ref<jhybridobject> jThis, jlong jsRuntimePointer, alias_ref<JObject> context);

        void onSurfaceCreated(alias_ref<JSurface> surface);
        void onSurfaceChanged(alias_ref<JSurface> surface, int width, int height);
        void onSurfaceDestroyed(alias_ref<JSurface> surface);
        void draw();

        Runtime *_runtime;
        global_ref<FaceDetectorView::javaobject> _javaPart;
        ANativeWindow *_nativeWindow = nullptr;
    };
}
