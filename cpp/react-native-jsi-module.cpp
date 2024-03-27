#include <jsi/jsi.h>
#include "react-native-jsi-module.h"

extern "C"
{
  double multiply(double a, double b); // Declaration of the Rust function
}

namespace jsimodule
{
  void bridgeJSIFunctions(Runtime &jsi)
  {
    // Define `multiplyJSI` using JSI idioms.
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

          return multiply(a, b);
        });

    // Export the `multiply` function to React Native's global object
    jsi.global().setProperty(jsi, "multiply", std::move(multiplyJSI));
  }

} // namespace jsimodule
