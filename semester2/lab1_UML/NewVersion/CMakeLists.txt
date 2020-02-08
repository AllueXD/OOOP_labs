cmake_minimum_required(VERSION 3.15)
project(NewVersion)

set(CMAKE_CXX_STANDARD 14)

add_executable(NewVersion Graph.h GraphMatrix.h GraphStruct.h AdditionalBoruvka.h tests.cpp GraphAlgorithms.h)