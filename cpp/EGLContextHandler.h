//
// Created by rodrigo gomes on 16/05/24.
//

#pragma once


#include <android/native_window.h>
#include <EGL/egl.h>



class EGLContextHandler {
public:
    EGLContextHandler();

    ~EGLContextHandler();

    bool initialize(ANativeWindow *nativeWindow);

    void terminate();

    void swapBuffers();

    int getWidth() const;

    int getHeight() const;
    
    int _width;
    int _height;

private:
    EGLDisplay _eglDisplay;
    EGLConfig _eglConfig;
    EGLSurface _eglSurface;
    EGLContext _eglContext;

};
