cmake_minimum_required(VERSION 3.4)
project(LocalWordCount)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Lib)

add_subdirectory(Deps)
add_subdirectory(LocalWordCount)
add_subdirectory(UnitTests)

enable_testing()
add_test(NAME ./unit_test COMMAND ./Test/unit_test)
