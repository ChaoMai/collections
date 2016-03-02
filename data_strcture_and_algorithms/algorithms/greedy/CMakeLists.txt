set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/greedy/src GREEDY_SOURCE_FILES)
add_executable(algorithms_greedy ${GREEDY_SOURCE_FILES})
