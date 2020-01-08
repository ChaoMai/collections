cmake_minimum_required(VERSION 3.2)
project(cpp_primer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# -fno-elide-constructors
set(CMAKE_CXX_FLAGS "-Weverything -Wno-c++11-extensions -Wno-c++98-compat -Wno-missing-prototypes -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
set(CMAKE_BUILD_TYPE "Debug")

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
