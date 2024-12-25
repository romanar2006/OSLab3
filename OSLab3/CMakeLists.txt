cmake_minimum_required(VERSION 3.10)
project(OSLab3)

set(CMAKE_CXX_FLAGS_DEBUG "/MDd")
set(CMAKE_CXX_FLAGS_RELEASE "/MD")
set(CMAKE_CXX_STANDARD 17)

add_library(MarkerThreads MarkerThreads.cpp MarkerThreads.h)

add_executable(OSLab3 main.cpp)

target_link_libraries(OSLab3 MarkerThreads)
