set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)

include_directories(${PROJECT_SOURCE_DIR}/dep/googletest/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/test/unit UNIT_TEST_SOURCE_FILES)
add_executable(unit_test.run ${UNIT_TEST_SOURCE_FILES})
target_link_libraries(unit_test.run gtest lib_hex_multiply)
