cmake_minimum_required(VERSION 3.16)
project(aoc_d1 VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED On)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_executable(aoc_d1 main.cpp)
