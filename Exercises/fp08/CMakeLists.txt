cmake_minimum_required(VERSION 3.13)
project(fp08)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(../cute_lib)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(fp08 ${SOURCE_FILES})     

