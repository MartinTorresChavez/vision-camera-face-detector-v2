package com.visioncamerafacedetector;

import android.util.Log;
import androidx.annotation.NonNull;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import java.lang.ref.WeakReference;


public class VisionCameraFaceDetectorModule extends com.visioncamerafacedetector.VisionCameraFaceDetectorSpec {
  public static final String NAME = "VisionCameraFaceDetector";
  private FaceDetectorViewManager faceDetectorViewManager;
  private final WeakReference<ReactApplicationContext> weakReactContext;

  VisionCameraFaceDetectorModule(ReactApplicationContext reactContext) {
    super(reactContext);
    this.weakReactContext = new WeakReference<>(reactContext);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  public FaceDetectorViewManager getFaceDetectorViewManager() {
    return faceDetectorViewManager;
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  public boolean install() {
    if (faceDetectorViewManager != null) {
      return true;
    }

    try {
      System.loadLibrary("faceDetector");
      ReactApplicationContext context = weakReactContext.get();
      if (context == null) {
        Log.e(NAME, "React Application Context was null!");
        return false;
      }
      faceDetectorViewManager = new FaceDetectorViewManager();
      return true;
    } catch (Exception exception) {
      Log.e(NAME, "Failed to initialize FaceDetectorViewManager!", exception);
      return false;
    }
  }

}
