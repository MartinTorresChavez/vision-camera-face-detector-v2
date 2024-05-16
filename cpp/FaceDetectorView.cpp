#include "FaceDetectorView.h"
#include <android/log.h>

#define LOG_TAG "FaceDetectorView"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace FaceDetector {
    using namespace facebook::jni;

    using TSelf = local_ref<HybridClass<FaceDetectorView>::jhybriddata>;

    FaceDetectorView::FaceDetectorView(const alias_ref<FaceDetectorView::jhybridobject> &javaThis,
                                       Runtime *runtime, alias_ref<JObject> context) {
        _javaPart = make_global(javaThis);
        _runtime = runtime;
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
        draw(); // Draw something on the surface
    }

    void FaceDetectorView::onSurfaceChanged(alias_ref<JSurface> surface, int width, int height) {
        LOGI("onSurfaceChanged called: width=%d, height=%d", width, height);
        draw(); // Redraw on the surface with the new size
    }

    void FaceDetectorView::onSurfaceDestroyed(alias_ref<JSurface> surface) {
        LOGI("onSurfaceDestroyed called");
        if (_nativeWindow) {
            ANativeWindow_release(_nativeWindow);
            _nativeWindow = nullptr;
        }
        LOGI("Native window destroyed");
    }

    void FaceDetectorView::draw() {
        if (!_nativeWindow) {
            return;
        }

        ANativeWindow_Buffer buffer;
        if (ANativeWindow_lock(_nativeWindow, &buffer, nullptr) == 0) {
            uint32_t* pixels = static_cast<uint32_t*>(buffer.bits);
            int width = buffer.width;
            int height = buffer.height;
            int stride = buffer.stride;

            // Fill the buffer with a solid color (e.g., red)
            uint32_t color = 0xFFFF0000; // ARGB format: 0xAARRGGBB
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    pixels[y * stride + x] = color;
                }
            }

            ANativeWindow_unlockAndPost(_nativeWindow);
        }
    }
}
