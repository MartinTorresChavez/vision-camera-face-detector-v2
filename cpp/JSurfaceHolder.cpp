//
// Created by rodrigo gomes on 16/05/24.
//

#include "JSurfaceHolder.h"

namespace FaceDetector {
    using namespace facebook::jni;

   local_ref<JSurface> JSurfaceHolder::getSurface() const {
        static auto method = javaClassStatic()->getMethod<local_ref<JSurface>()>("getSurface");
        return method(self());
    }

    ANativeWindow* JSurface::getNativeWindow() const {
        auto env = facebook::jni::Environment::current();
        jobject surface = self();
        return ANativeWindow_fromSurface(env, surface);
    }

}
