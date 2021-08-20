cmake_minimum_required(VERSION 3.20)
project(ch5)

set(CMAKE_CXX_STANDARD 11)

add_executable(ch5 "ch5/ch5.cpp" "ch5/ch5.h")

add_executable(ch5_ex "ch5_ex/ch5_ex.cpp" "ch5_ex/ch5_ex.h")

add_executable(ch5_hybrid "hybrid/hybrid.cpp" "hybrid/hybrid.h")

add_executable(ch5_inher "inher/classes.cpp" "inher/classes.h")
