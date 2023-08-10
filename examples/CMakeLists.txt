cmake_minimum_required(VERSION 3.10)

project(air_examples)

set(CMAKE_CXX_STANDARD 17)

add_executable(app main.cc)
target_compile_features(app PUBLIC cxx_std_17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fcolor-diagnostics")

target_include_directories(app PUBLIC ../include)
