//
// Created by rodrigo gomes on 14/05/24.
//

#include "FaceDetectorView.h"
#include <fbjni/fbjni.h>
#include <jni.h>

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *)
{
  return facebook::jni::initialize(vm, [] {
     FaceDetector::FaceDetectorView::registerNatives();
  });
}

