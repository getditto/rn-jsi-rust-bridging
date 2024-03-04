#ifdef __cplusplus
#import "react-native-jsi-module.h"
#endif

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNJsiModuleSpec.h"

@interface JsiModule : NSObject <NativeJsiModuleSpec>
#else
#import <React/RCTBridgeModule.h>

@interface JsiModule : NSObject <RCTBridgeModule>
#endif

@end
