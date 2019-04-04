cmake_minimum_required(VERSION 3.13)
project(fp05)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(../cute_lib)

add_executable(fp05
        src/Graph.h
        src/MutablePriorityQueue.h
        src/Test.cpp
        CMakeLists.txt
        Icon\r
        Makefile)
