import { NativeModules, Platform, requireNativeComponent } from 'react-native';

const FaceDetectorView = requireNativeComponent('FaceDetectorView');

const LINKING_ERROR =
  `The package 'react-native-vision-camera-face-detector' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

// @ts-expect-error
const isTurboModuleEnabled = global.__turboModuleProxy != null;

const VisionCameraFaceDetectorModule = isTurboModuleEnabled
  ? require('./NativeVisionCameraFaceDetector').default
  : NativeModules.VisionCameraFaceDetector;

const VisionCameraFaceDetector = VisionCameraFaceDetectorModule
  ? VisionCameraFaceDetectorModule
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

export function multiply(a: number, b: number): Promise<number> {
  return VisionCameraFaceDetector.multiply(a, b);
}

export { FaceDetectorView };
