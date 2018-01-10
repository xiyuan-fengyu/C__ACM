cmake_minimum_required(VERSION 3.8)
project(C__ACM)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/Solutions.h src/model/ListNode.cpp src/model/ListNode.h src/util/util.cpp src/util/util.h)
add_executable(C__ACM ${SOURCE_FILES})