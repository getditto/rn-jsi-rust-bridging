cmake_minimum_required(VERSION 3.4.1)
project(JsiModule)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)

add_library(react-native-jsi-module SHARED
    ../cpp/react-native-jsi-module.cpp
    cpp-adapter.cpp
)

# Specifies a path to native header files.
include_directories(
    ../cpp
)

add_library(rust_multiply STATIC IMPORTED)
set_target_properties(rust_multiply PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/librust_multiply_lib.a")

find_package(ReactAndroid REQUIRED CONFIG)
target_link_libraries(
    react-native-jsi-module
    ReactAndroid::jsi
    android
    rust_multiply
)
