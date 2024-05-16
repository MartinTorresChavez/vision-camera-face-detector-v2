//
// Created by rodrigo gomes on 16/05/24.
//

#include "JSurfaceView.h"
#include "JSurfaceHolder.h"

namespace FaceDetector {
    using namespace facebook::jni;


    facebook::jni::local_ref<JSurfaceView> JSurfaceView::create(alias_ref<JObject> context) {
        static auto ctor = javaClassStatic()->getConstructor<JSurfaceView::javaobject(alias_ref<JContext>)>();
        return javaClassStatic()->newObject(ctor, static_ref_cast<JContext>(context));
    }

    local_ref<JSurfaceHolder> JSurfaceView::getHolder() const {
        static auto method = javaClassStatic()->getMethod<local_ref<JSurfaceHolder>()>("getHolder");
        return method(self());
    }

}
