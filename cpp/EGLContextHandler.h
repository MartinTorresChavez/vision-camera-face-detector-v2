//
// Created by rodrigo gomes on 16/05/24.
//

#pragma once

#include <android/native_window.h>
#include <EGL/egl.h>

namespace FaceDetector {

    class EGLContextHandler {
    public:
        EGLContextHandler();

        ~EGLContextHandler();

        bool initialize(ANativeWindow *nativeWindow);

        void terminate();

        void swapBuffers();

        int getWidth() const;

        int getHeight() const;

    private:
        EGLDisplay _eglDisplay;
        EGLConfig _eglConfig;
        EGLSurface _eglSurface;
        EGLContext _eglContext;
        int _width;
        int _height;
    };

}

