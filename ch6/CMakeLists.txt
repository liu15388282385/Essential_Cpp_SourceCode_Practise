cmake_minimum_required(VERSION 3.20)
project(ch6)

set(CMAKE_CXX_STANDARD 11)

add_executable(ch6 "ch6/ch6.cpp" "ch6/ch6.h")

add_executable(ch6_ex "ch6_ex/ch6_ex.cpp" "ch6_ex/ch6_ex.h")

add_executable(btree "binaryTree/btree.cpp" "binaryTree/btree.h")

add_executable(s_main "strategy/s_main.cpp" "strategy/s_main.h")