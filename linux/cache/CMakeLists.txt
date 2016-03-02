cmake_minimum_required(VERSION 3.2)
project(cache)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -g")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src CACHE_SOURCE_FILES)

add_executable(cache ${CACHE_SOURCE_FILES})
