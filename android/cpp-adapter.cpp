#include <jni.h>
#include <jsi/jsi.h>
#include "react-native-jsi-module.h"

using namespace facebook::jsi;

// Optional:
void bridgePlatformFunctions(Runtime &jsi);

extern "C" JNIEXPORT void JNICALL
Java_com_jsimodule_JsiModuleModule_jniBridgeJSIFunctions(JNIEnv *env, jobject thiz, jobject context,
                                                         jlong jsi_pointer)
{
    Runtime *jsi = reinterpret_cast<Runtime *>(jsi_pointer);
    if (jsi)
    {
        jsimodule::bridgeJSIFunctions(*jsi);

        // Optional: bridge some platform specific logic too.
        bridgePlatformFunctions(*jsi);
    }
}

void bridgePlatformFunctions(Runtime &jsi)
{
    auto getDeviceName = Function::createFromHostFunction(jsi,
                                                          PropNameID::forAscii(jsi, "getDeviceName"),
                                                          0,
                                                          [](Runtime &runtime,
                                                             const Value &thisValue,
                                                             const Value *arguments,
                                                             size_t count) -> Value
                                                          {
                                                              // JNI logic for another time!
                                                              return Value(runtime, String::createFromAscii(runtime, "Not yet implemented."));
                                                          });

    jsi.global().setProperty(jsi, "getDeviceName", std::move(getDeviceName));
}