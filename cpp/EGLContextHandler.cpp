//
// Created by rodrigo gomes on 16/05/24.
//

#include "EGL/egl.h"
#include "EGLContextHandler.h"
#include <android/log.h>

#define LOG_TAG "EGLContextHandler"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace FaceDetector {
    EGLContextHandler::EGLContextHandler()
            : _eglDisplay(EGL_NO_DISPLAY), _eglSurface(EGL_NO_SURFACE), _eglContext(EGL_NO_CONTEXT),
              _width(0), _height(0) {}

    EGLContextHandler::~EGLContextHandler() {
        terminate();
    }

    bool EGLContextHandler::initialize(ANativeWindow* nativeWindow) {
        _eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (_eglDisplay == EGL_NO_DISPLAY) {
            LOGI("Failed to get EGL display");
            return false;
        }

        if (!eglInitialize(_eglDisplay, nullptr, nullptr)) {
            LOGI("Failed to initialize EGL");
            return false;
        }

        const EGLint configAttribs[] = {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_DEPTH_SIZE, 16,
                EGL_NONE
        };


        EGLint numConfigs;
        if (!eglChooseConfig(_eglDisplay, configAttribs, &_eglConfig, 1, &numConfigs) || numConfigs < 1) {
            LOGI("Failed to choose EGL config");
            return false;
        }

        _eglSurface = eglCreateWindowSurface(_eglDisplay, _eglConfig, nativeWindow, nullptr);
        if (_eglSurface == EGL_NO_SURFACE) {
            LOGI("Failed to create EGL surface");
            return false;
        }

        const EGLint contextAttribs[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2,
                EGL_NONE
        };
        _eglContext = eglCreateContext(_eglDisplay, _eglConfig, EGL_NO_CONTEXT, contextAttribs);
        if (_eglContext == EGL_NO_CONTEXT) {
            LOGI("Failed to create EGL context");
            return false;
        }

        if (!eglMakeCurrent(_eglDisplay, _eglSurface, _eglSurface, _eglContext)) {
            LOGI("Failed to make EGL context current");
            return false;
        }

        _width = ANativeWindow_getWidth(nativeWindow);
        _height = ANativeWindow_getHeight(nativeWindow);

        return true;
    }

    void EGLContextHandler::terminate() {
        if (_eglDisplay != EGL_NO_DISPLAY) {
            eglMakeCurrent(_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (_eglContext != EGL_NO_CONTEXT) {
                eglDestroyContext(_eglDisplay, _eglContext);
            }
            if (_eglSurface != EGL_NO_SURFACE) {
                eglDestroySurface(_eglDisplay, _eglSurface);
            }
            eglTerminate(_eglDisplay);
        }
        _eglDisplay = EGL_NO_DISPLAY;
        _eglSurface = EGL_NO_SURFACE;
        _eglContext = EGL_NO_CONTEXT;
    }

    void EGLContextHandler::swapBuffers() {
        if (_eglDisplay != EGL_NO_DISPLAY && _eglSurface != EGL_NO_SURFACE) {
            eglSwapBuffers(_eglDisplay, _eglSurface);
        }
    }

    int EGLContextHandler::getWidth() const {
        return _width;
    }

    int EGLContextHandler::getHeight() const {
        return _height;
    }

}
