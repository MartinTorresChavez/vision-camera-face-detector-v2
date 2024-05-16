//
// Created by rodrigo gomes on 15/05/24.
//

#pragma once

#include <fbjni/fbjni.h>
#include <jsi/jsi.h>

namespace FaceDetector {
    using namespace facebook;
    using namespace facebook::jni;

    class FaceDetectorView : public HybridClass<FaceDetectorView> {
    public:
        ~FaceDetectorView();
        static void registerNatives();


    private:
        friend HybridBase;
        jni::global_ref<FaceDetectorView::javaobject> _javaPart;
        jsi::Runtime *_runtime;

        static auto constexpr TAG = "FaceDetectorView";
        static auto constexpr kJavaDescriptor = "Lcom/visioncamerafacedetector/FaceDetectorView;";

        explicit FaceDetectorView(const jni::alias_ref<FaceDetectorView::jhybridobject> &javaThis);

        static jni::local_ref<jhybriddata>
        initHybrid(jni::alias_ref<jhybridobject> javaThis);
    };

}
