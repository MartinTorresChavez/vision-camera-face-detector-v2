//
// Created by rodrigo gomes on 20/05/24.
//


#ifndef GLOBAL_H
#define GLOBAL_H

#include "EGLContextHandler.h"
#include <memory>

extern std::shared_ptr<EGLContextHandler> globalEglHandler;
extern ANativeWindow *_nativeWindow;

#endif // GLOBAL_H
