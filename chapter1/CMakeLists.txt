#最低版本
cmake_minimum_required(VERSION 3.23)
#项目名称
project(ch1)
#语言标准
set(CMAKE_CXX_STANDARD 14)

#可执行文件
add_executable(ch1 main.cpp ch1/ch1.cpp ch1/ch1.h)

add_executable(ch1_ex "ch1_ex/ch1_ex.cpp" "ch1_ex/ch1_ex.h")

