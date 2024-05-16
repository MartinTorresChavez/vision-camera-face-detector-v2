//
// Created by rodrigo gomes on 15/05/24.
//

#include "JSurfaceHolder.h"
#include "JSurfaceView.h"

#include "FaceDetectorView.h"
#include <fbjni/ByteBuffer.h>
#include <memory>
#include <string>
#include <utility>
#include <jsi/jsi.h>

namespace FaceDetector {
    using namespace facebook::jni;

    using TSelf = local_ref<HybridClass<FaceDetectorView>::jhybriddata>;

    FaceDetectorView::FaceDetectorView(const jni::alias_ref<FaceDetectorView::jhybridobject> &javaThis,
                                       jsi::Runtime *runtime, jni::alias_ref<JObject> context) {
        _javaPart = make_global(javaThis);
        _runtime = runtime;
        auto surfaceView = JSurfaceView::create(context);
        auto surfaceHolder = surfaceView->getHolder();
        auto surface = surfaceHolder->getSurface();
        _nativeWindow = surface->getNativeWindow();
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "Native window: %p", _nativeWindow);
    }

    FaceDetectorView::~FaceDetectorView() {
        if (_nativeWindow) {
            ANativeWindow_release(_nativeWindow);
        }
    }

    void FaceDetectorView::registerNatives() {
        registerHybrid({makeNativeMethod("initHybrid", FaceDetectorView::initHybrid)});
    }

    jsi::Runtime *FaceDetectorView::getJSRuntime() {
        return _runtime;
    }

    ANativeWindow* FaceDetectorView::getNativeWindow() {
        return _nativeWindow;
    }

    TSelf FaceDetectorView::initHybrid(alias_ref<jhybridobject> jThis, jlong jsRuntimePointer, alias_ref<JObject> context) {
        auto jsRuntime = reinterpret_cast<jsi::Runtime *>(jsRuntimePointer);
        return makeCxxInstance(jThis, jsRuntime, context);
    }

}
