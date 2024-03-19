#ifndef JSIMODULE_H
#define JSIMODULE_H

#include <jsi/jsi.h>

using namespace facebook::jsi;

namespace jsimodule {
void bridgeJSIFunctions(Runtime &jsi);
}

#endif /* JSIMODULE_H */
