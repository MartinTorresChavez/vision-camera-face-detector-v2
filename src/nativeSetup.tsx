import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'vision-camera-face-detector' doesn't seem to be linked. Make sure: \n\n` +
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

(() => {
  console.log(
    'calling visioncamerafacedetector.install() -->',
    VisionCameraFaceDetector.install
  );
  VisionCameraFaceDetector.install();
})();
