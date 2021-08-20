#最低版本
cmake_minimum_required(VERSION 3.19)
#项目名称
project(ch1)
#语言标准
set(CMAKE_CXX_STANDARD 14)

#可执行文件
add_executable(ch1 main.cpp ch1/ch1.cpp ch1/ch1.h)

add_executable(ex1-7 "ch1_ex/ex 1-7/Ex1_7.cpp")

add_executable(ex1-6 "ch1_ex/ex 1-6/Ex1_6.cpp" "ch1_ex/ex 1-6/Ex1_6.h")

add_executable(ex1-5 "ch1_ex/ex 1-5/Ex1_5.cpp" "ch1_ex/ex 1-5/Ex1_5.h")
