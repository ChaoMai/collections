set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/pattern_matching/src PATTERN_MATCHING_SOURCE_FILES)
add_executable(algorithms_pattern_matching ${PATTERN_MATCHING_SOURCE_FILES})
