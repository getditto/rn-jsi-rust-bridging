#include <jni.h>
#include "react-native-jsi-module.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_jsimodule_JsiModuleModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return jsimodule::multiply(a, b);
}
