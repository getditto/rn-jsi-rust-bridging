package com.jsimodule;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = JsiModuleModule.NAME)
public class JsiModuleModule extends ReactContextBaseJavaModule {
  public static final String NAME = "JsiModule";

  private native void jniBridgeJSIFunctions(ReactApplicationContext context, long jsi_pointer);

  public JsiModuleModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  public boolean bridgeJSIFunctions() {
    try {
      System.loadLibrary("react-native-jsi-module");

      ReactApplicationContext context = getReactApplicationContext();
      jniBridgeJSIFunctions(
          context,
          context.getJavaScriptContextHolder().get()
      );
      return true;
    } catch (Exception exception) {
      return false;
    }
  }
}
