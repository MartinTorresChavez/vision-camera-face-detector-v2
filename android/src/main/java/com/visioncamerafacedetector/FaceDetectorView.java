package com.visioncamerafacedetector;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.SurfaceTexture;
import android.util.Log;
import android.view.Surface;
import android.view.TextureView;
import android.view.TextureView.SurfaceTextureListener;

import androidx.annotation.NonNull;

import com.facebook.jni.HybridData;
import com.facebook.jni.annotations.DoNotStrip;
import com.facebook.react.uimanager.ThemedReactContext;

@SuppressLint("ViewConstructor")
public class FaceDetectorView extends TextureView implements SurfaceTextureListener {
  @DoNotStrip
  private final HybridData mHybridData;
  @DoNotStrip
  private Surface mSurface;

  @SuppressWarnings("JavaJniMissingFunction")
  private static native HybridData initHybrid(long jsRuntimeHolder, Object context);

  @SuppressWarnings("JavaJniMissingFunction")
  private native void nativeSurfaceCreated(Surface surface);

  @SuppressWarnings("JavaJniMissingFunction")
  private native void nativeSurfaceChanged(Surface surface, int width, int height);

  @SuppressWarnings("JavaJniMissingFunction")
  private native void nativeSurfaceDestroyed(Surface surface);

  public FaceDetectorView(ThemedReactContext context) {
    super(context);
    setSurfaceTextureListener(this);
    var jsRuntimeHolder = context.getJavaScriptContextHolder();
    if (jsRuntimeHolder == null) {
      throw new IllegalStateException("JS runtime holder is not available");
    }
    mHybridData = initHybrid(jsRuntimeHolder.get(), context);
  }

  @Override
  public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int width, int height) {
    mSurface = new Surface(surfaceTexture);
    nativeSurfaceCreated(mSurface); // Notify native code that the surface is created
  }

  @Override
  public void onSurfaceTextureSizeChanged(SurfaceTexture surfaceTexture, int width, int height) {
    nativeSurfaceChanged(mSurface, width, height); // Notify native code that the surface size or format changed
  }

  @Override
  public boolean onSurfaceTextureDestroyed(SurfaceTexture surfaceTexture) {
    nativeSurfaceDestroyed(mSurface); // Notify native code that the surface is destroyed
    mSurface.release();
    mSurface = null;
    return true;
  }

  @Override
  public void onSurfaceTextureUpdated(SurfaceTexture surfaceTexture) {
    // This can be used to handle updates to the surface texture if needed
    Log.d("FaceDetectorView", "Surface texture updated");
  }
}
