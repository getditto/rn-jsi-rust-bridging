import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'react-native-jsi-module' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

const JsiModule =
  NativeModules.JsiModule ??
  new Proxy(
    {},
    {
      get() {
        throw new Error(LINKING_ERROR);
      },
    }
  );

const jsiCore = global as unknown as {
  multiply(a: number, b: number): number;
};

JsiModule.bridgeJSIFunctions();

export function multiply(a: number, b: number): number {
  return jsiCore.multiply(a, b);
}
