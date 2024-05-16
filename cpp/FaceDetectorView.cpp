//
// Created by rodrigo gomes on 15/05/24.
//

#include "FaceDetectorView.h"
#include <fbjni/ByteBuffer.h>
#include <memory>
#include <string>
#include <utility>
#include <jsi/jsi.h>

namespace FaceDetector {
    using namespace facebook::jni;

    using TSelf = local_ref<HybridClass<FaceDetectorView>::jhybriddata>;

    FaceDetectorView::FaceDetectorView(const jni::alias_ref<FaceDetectorView::jhybridobject> &javaThis) {
        _javaPart = make_global(javaThis);
    }

    FaceDetectorView::~FaceDetectorView() {
    }

    void FaceDetectorView::registerNatives() {
        registerHybrid({makeNativeMethod("initHybrid", FaceDetectorView::initHybrid)});
    }

    TSelf FaceDetectorView::initHybrid(alias_ref<jhybridobject> jThis) {
        return makeCxxInstance(jThis);
    }

}
