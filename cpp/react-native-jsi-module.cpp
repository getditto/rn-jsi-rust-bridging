#include "react-native-jsi-module.h"

extern "C"
{
  // For instance, C++'s `double` type is the equivalent of Rust's `f64`
  double rust_multiply(double a, double b);
}

namespace jsimodule
{
  void bridgeJSIFunctions(Runtime &jsi)
  {
    auto multiplyJSI = Function::createFromHostFunction(
        jsi,
        PropNameID::forAscii(jsi, "multiplyJSI"),
        2, // number of arguments
        [](Runtime &runtime, const Value &thisValue, const Value *arguments, size_t count) -> Value
        {
          if (count < 2)
          {
            throw JSError(runtime, "multiply() expects 2 arguments");
          }

          double a = arguments[0].asNumber();
          double b = arguments[1].asNumber();

          double ret = rust_multiply(a, b);

          return Value(ret);
        });

    jsi.global().setProperty(jsi, "multiply", std::move(multiplyJSI));
  }

} // namespace jsimodule
