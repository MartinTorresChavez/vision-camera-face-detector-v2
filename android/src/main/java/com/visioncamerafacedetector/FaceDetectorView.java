package com.visioncamerafacedetector;

import android.content.Context;
import android.view.View;
import com.facebook.jni.HybridData;
import com.facebook.jni.annotations.DoNotStrip;




public class FaceDetectorView extends View {
  @DoNotStrip
  private final HybridData mHybridData;

  @SuppressWarnings("JavaJniMissingFunction")
  private static native HybridData initHybrid();

  public FaceDetectorView(Context context) {
    super(context);
//    VisionCameraFaceDetectorModule faceDetectorModule = ((ReactContext) context).getNativeModule(VisionCameraFaceDetectorModule.class);
      mHybridData = initHybrid();
  }

}
