cmake_minimum_required(VERSION 3.10)
project(OSLab3_tests)

set(CMAKE_CXX_FLAGS_DEBUG "/MDd")
set(CMAKE_CXX_FLAGS_RELEASE "/MD")
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(OSLab3_tests OSLab3_tests/test.cpp ../OSLab3/MarkerThreads.cpp)

target_link_libraries(OSLab3_tests PRIVATE MarkerThreads gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(OSLab3_tests)
