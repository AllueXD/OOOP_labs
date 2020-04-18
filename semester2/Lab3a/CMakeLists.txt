cmake_minimum_required(VERSION 3.14)
project(Lab3a)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build tests" ON)


if (BUILD_TESTS)
    add_executable(tests tests.cpp)
endif()

add_executable(Lab3a main.cpp)