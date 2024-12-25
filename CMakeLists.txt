cmake_minimum_required(VERSION 3.10)
project(OSLab3)

set(CMAKE_CXX_FLAGS_DEBUG "/MDd")  # Для режима Debug
set(CMAKE_CXX_FLAGS_RELEASE "/MD") # Для режима Release
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(OSLab3)
add_subdirectory(OSLab3_tests)
