package com.visioncamerafacedetector;

import androidx.annotation.NonNull;

import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

public class FaceDetectorViewManager extends SimpleViewManager<FaceDetectorView> {
    @NonNull
    @Override
    public String getName() {
      return "FaceDetectorView";
    }

    @NonNull
    @Override
    public FaceDetectorView createViewInstance(@NonNull ThemedReactContext reactContext) {
      return new FaceDetectorView(reactContext);
    }
  }

