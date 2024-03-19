#include <jsi/jsi.h>
#include "react-native-jsi-module.h"

extern "C"
{
  int multiply(int a, int b); // Declaration of the Rust function
}

namespace jsimodule
{
  void bridgeJSIFunctions(Runtime &jsi)
  {
    // Define the `multiply` function using JSI idioms
    auto multiplyFunction = Function::createFromHostFunction(
        jsi,
        PropNameID::forAscii(jsi, "multiplyFunction"),
        2, // number of arguments
        [](Runtime &runtime, const Value &thisValue, const Value *arguments, size_t count) -> Value
        {
          if (count < 2)
          {
            throw JSError(runtime, "multiply() expects 2 arguments");
          }

          double a = arguments[0].asNumber();
          double b = arguments[1].asNumber();

          return Value();
//          return multiply(a, b);
        });

    // Export the `multiply` function to React Native's global object
    jsi.global().setProperty(jsi, "multiply", std::move(multiplyFunction));
  }

} // namespace jsimodule
