cmake_minimum_required(VERSION 3.20)
project(ch7)

set(CMAKE_CXX_STANDARD 11)

add_executable(ch7 "ch7/ch7.cpp")

add_executable(ch7_ex "ch7_ex/ch7_ex.cpp" "ch7_ex/ch7_ex.h")