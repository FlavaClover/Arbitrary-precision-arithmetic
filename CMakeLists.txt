cmake_minimum_required(VERSION 3.17)
project(Arbitrary_precision_arithmetic)

set(CMAKE_CXX_STANDARD 14)

add_executable(Arbitrary_precision_arithmetic main.cpp Arithmetic.h Arithmetic.cpp)