#ifdef __cplusplus
#import "react-native-vision-camera-face-detector.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNVisionCameraFaceDetectorSpec.h"

@interface VisionCameraFaceDetector : NSObject <NativeVisionCameraFaceDetectorSpec>
#else
#import <React/RCTBridgeModule.h>

@interface VisionCameraFaceDetector : NSObject <RCTBridgeModule>
#endif

@end
