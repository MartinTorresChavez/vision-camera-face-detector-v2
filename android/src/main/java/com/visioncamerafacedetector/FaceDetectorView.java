package com.visioncamerafacedetector;


import android.view.View;
import com.facebook.jni.HybridData;
import com.facebook.jni.annotations.DoNotStrip;
import com.facebook.react.uimanager.ThemedReactContext;


public class FaceDetectorView extends View {
  @DoNotStrip
  private final HybridData mHybridData;

  @SuppressWarnings("JavaJniMissingFunction")
  private static native HybridData initHybrid(long jsRuntimeHolder, Object context);

  public FaceDetectorView(ThemedReactContext context) {
    super(context);
      var jsRuntimeHolder = context.getJavaScriptContextHolder();
      if (jsRuntimeHolder == null) {
        throw new IllegalStateException("JS runtime holder is not available");
      }
      mHybridData = initHybrid(jsRuntimeHolder.get(), context);
  }

}
