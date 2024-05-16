package com.visioncamerafacedetector;

import com.facebook.proguard.annotations.DoNotStrip;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactMethod;

abstract class VisionCameraFaceDetectorSpec extends ReactContextBaseJavaModule {
  VisionCameraFaceDetectorSpec(ReactApplicationContext context) {
    super(context);
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  @DoNotStrip
  public abstract boolean install();
}
