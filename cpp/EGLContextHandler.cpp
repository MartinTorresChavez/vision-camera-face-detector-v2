//
// Created by rodrigo gomes on 16/05/24.
//

#include <EGL/egl.h>
#include "EGLContextHandler.h"
#include "react_native_rcore.h"
#include <android/log.h>



#define LOG_TAG "EGLContextHandler"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)



EGLContextHandler::EGLContextHandler()
        : _eglDisplay(EGL_NO_DISPLAY), _eglSurface(EGL_NO_SURFACE), _eglContext(EGL_NO_CONTEXT),
          _width(0), _height(0) {}

EGLContextHandler::~EGLContextHandler() {
    terminate();
}

bool EGLContextHandler::initialize(ANativeWindow* nativeWindow) {
    _eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);


    CORE.Window.display.width = 500;
    CORE.Window.display.height = 500;
    CORE.Window.render.width = 500;
    CORE.Window.render.height = 500;

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


    const EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    eglBindAPI(EGL_OPENGL_ES_API);

    _eglContext = eglCreateContext(_eglDisplay, _eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if (_eglContext == EGL_NO_CONTEXT) {
        LOGI("Failed to create EGL context");
        return false;
    }

    EGLint displayFormat = 0;

    // EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is guaranteed to be accepted by ANativeWindow_setBuffersGeometry()
    // As soon as we picked a EGLConfig, we can safely reconfigure the ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID
    eglGetConfigAttrib(_eglDisplay, _eglConfig, EGL_NATIVE_VISUAL_ID, &displayFormat);

    ANativeWindow_setBuffersGeometry(nativeWindow, 500, 500, displayFormat);

    _eglSurface = eglCreateWindowSurface(_eglDisplay, _eglConfig, nativeWindow, nullptr);
    if (_eglSurface == EGL_NO_SURFACE) {
        LOGI("Failed to create EGL surface");
        return false;
    }

    if (eglMakeCurrent(_eglDisplay, _eglSurface, _eglSurface, _eglContext) == EGL_FALSE) {
        LOGI("Failed to make EGL context current");
        return false;
    }



    LOGI("DISPLAY: Device initialized successfully");
    LOGI("    > Display size: %i x %i", CORE.Window.display.width, CORE.Window.display.height);
    LOGI("    > Screen size:  %i x %i", CORE.Window.screen.width, CORE.Window.screen.height);
    LOGI("    > Render size:  %i x %i", CORE.Window.render.width, CORE.Window.render.height);
    LOGI("    > Viewport offsets: %i, %i", CORE.Window.renderOffset.x, CORE.Window.renderOffset.y);


    rlLoadExtensions((void*)eglGetProcAddress);

    CORE.Window.ready = true;
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


