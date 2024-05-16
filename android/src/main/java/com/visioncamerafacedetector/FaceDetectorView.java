package com.visioncamerafacedetector;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;

import com.facebook.jni.HybridData;
import com.facebook.jni.annotations.DoNotStrip;
import com.facebook.react.bridge.ReactContext;

public class FaceDetectorView extends View {

  @DoNotStrip
  private final HybridData mHybridData;


  @SuppressWarnings("unused")
  private native HybridData initHybrid();

  public FaceDetectorView(Context context) {
    super(context);
//    VisionCameraFaceDetectorModule faceDetectorModule = ((ReactContext) context).getNativeModule(VisionCameraFaceDetectorModule.class);
      mHybridData = initHybrid();
  }

}
