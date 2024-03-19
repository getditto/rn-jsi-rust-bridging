#import "JsiModule.h"
#import "react-native-jsi-module.h"

#import <React/RCTBridge+Private.h>
#import <jsi/jsi.h>

using namespace facebook::jsi;

@implementation JsiModule

RCT_EXPORT_MODULE()

@synthesize bridge = _bridge;
@synthesize methodQueue = _methodQueue;

// Ensures JSI functions will be made available from the main thread.
+ (BOOL)requiresMainQueueSetup {
  return YES;
}

// Ensures no JavaScript will be executed until JSI is set up.
RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(bridgeJSIFunctions) {
  RCTBridge* bridge = [RCTBridge currentBridge];
  RCTCxxBridge* cxxBridge = (RCTCxxBridge*)bridge;
  Runtime *jsi = (Runtime *) cxxBridge.runtime;

  jsimodule::bridgeJSIFunctions(*jsi);

  // Optional: bridge iOS-platform specific logic
  bridgePlatformFunctions(*jsi);

  return @true;
}

// Optional:
static void bridgePlatformFunctions(Runtime &jsi) {
  auto getDeviceName = Function::createFromHostFunction(jsi,
                                                        PropNameID::forAscii(jsi, "getDeviceName"),
                                                        0,
                                                        [](Runtime &runtime,
                                                           const Value &thisValue,
                                                           const Value *arguments,
                                                           size_t count) -> Value {
    return String::createFromUtf8(runtime, [[[UIDevice currentDevice] name] UTF8String]);
  });

  jsi.global().setProperty(jsi, "getDeviceName", std::move(getDeviceName));
}

@end
