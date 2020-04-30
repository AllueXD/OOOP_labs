cmake_minimum_required(VERSION 3.14)
project(Lab3a)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_BENCHMARK "Build benchmarks" ON)
option(BUILD_TESTS "Build tests" ON)

add_executable(main main.cpp)

if (BUILD_BENCHMARK)
    add_executable(mybenchmark mybenchmark.cpp)
    add_subdirectory(3rdparty/benchmark)
    target_link_libraries(mybenchmark benchmark::benchmark)
endif()

if (BUILD_TESTS)
    add_executable(tests tests.cpp)
endif()


