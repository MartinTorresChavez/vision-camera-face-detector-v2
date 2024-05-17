#include "FaceDetectorView.h"
#include <android/log.h>
#include "raylib.h"
#include "EGLContextHandler.h"

#define LOG_TAG "FaceDetectorView"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace FaceDetector {
    using namespace facebook::jni;


    using TSelf = local_ref<HybridClass<FaceDetectorView>::jhybriddata>;

    FaceDetectorView::FaceDetectorView(const alias_ref<FaceDetectorView::jhybridobject> &javaThis,
                                       Runtime *runtime, alias_ref<JObject> context) {
        _javaPart = make_global(javaThis);
        _runtime = runtime;
        _eglHandler = std::make_unique<EGLContextHandler>();

    }

    FaceDetectorView::~FaceDetectorView() {
        if (_nativeWindow) {
            ANativeWindow_release(_nativeWindow);
        }
    }

    void FaceDetectorView::registerNatives() {
        registerHybrid({
               makeNativeMethod("initHybrid", FaceDetectorView::initHybrid),
               makeNativeMethod("nativeSurfaceCreated", FaceDetectorView::onSurfaceCreated),
               makeNativeMethod("nativeSurfaceChanged", FaceDetectorView::onSurfaceChanged),
               makeNativeMethod("nativeSurfaceDestroyed", FaceDetectorView::onSurfaceDestroyed)
        });
    }

    Runtime *FaceDetectorView::getJSRuntime() {
        return _runtime;
    }

    ANativeWindow* FaceDetectorView::getNativeWindow() {
        return _nativeWindow;
    }

    TSelf FaceDetectorView::initHybrid(alias_ref<jhybridobject> jThis, jlong jsRuntimePointer, alias_ref<JObject> context) {
        auto jsRuntime = reinterpret_cast<Runtime *>(jsRuntimePointer);
        return makeCxxInstance(jThis, jsRuntime, context);
    }

    void FaceDetectorView::onSurfaceCreated(alias_ref<JSurface> surface) {
        LOGI("onSurfaceCreated called");
        _nativeWindow = ANativeWindow_fromSurface(facebook::jni::Environment::current(), surface.get());
        LOGI("Native window created: %p", _nativeWindow);

        if (_eglHandler->initialize(_nativeWindow)) {
            InitWindow(_eglHandler->getWidth(), _eglHandler->getHeight(), "Raylib on ANativeWindow");
//            SetTargetFPS(60);
            _renderThread = std::thread(&FaceDetectorView::renderLoop, this);
        } else {
            LOGI("Failed to initialize EGL context");
        }
    }



    void FaceDetectorView::onSurfaceChanged(alias_ref<JSurface> surface, int width, int height) {
        LOGI("onSurfaceChanged called: width=%d, height=%d", width, height);
        SetWindowSize(width, height);
    }

    void FaceDetectorView::onSurfaceDestroyed(alias_ref<JSurface> surface) {
        LOGI("onSurfaceDestroyed called");
        if (_nativeWindow) {
            ANativeWindow_release(_nativeWindow);
            _nativeWindow = nullptr;
        }
        LOGI("Native window destroyed");
    }

    void FaceDetectorView::renderLoop() {
        while (_nativeWindow) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello, Raylib!", 10, 10, 20, GREEN);
            EndDrawing();
        }
    }

}
