set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/sort/src SORT_SOURCE_FILES)
add_executable(algorithms_sort ${SORT_SOURCE_FILES})
