//
// Created by rodrigo gomes on 14/05/24.
//

#include <fbjni/fbjni.h>
#include <jni.h>

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *)
{
  return facebook::jni::initialize(vm, [] {

  });
}