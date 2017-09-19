cmake_minimum_required(VERSION 3.8)
project(C__ACM)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Solutions.cpp Solutions.h util/Util.cpp util/Util.h)
add_executable(C__ACM ${SOURCE_FILES})