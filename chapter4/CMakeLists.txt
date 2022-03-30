cmake_minimum_required(VERSION 3.23)
project(ch4)

set(CMAKE_CXX_STANDARD 11)

add_executable(ch4  "ch4/ch4.cpp" "ch4/ch4.h")

add_executable(ch4_ex "ch4_ex/ch4_ex.cpp" "ch4_ex/ch4_ex.h" "stack.h")

add_executable(polymorphic "polymorphic/polymorphic.cpp")
