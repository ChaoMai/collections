cmake_minimum_required(VERSION 2.8.7)
project(cml)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -Weverything -Wno-c++11-extensions \
-Wno-c++98-compat -Wno-c++98-compat-pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} - O3")

add_subdirectory(backtracking)
add_subdirectory(dynamic_programming)
add_subdirectory(graph)
add_subdirectory(greedy)
add_subdirectory(pattern_matching)
add_subdirectory(sort)
