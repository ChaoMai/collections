set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/backtracking/src BACKTRACKING_SOURCE_FILES)
add_executable(algorithms_backtracking ${BACKTRACKING_SOURCE_FILES})
