set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/dynamic_programming/src
  DYNAMIC_PROGRAMMING_SOURCE_FILES)
add_executable(algorithms_dynamic_programming ${DYNAMIC_PROGRAMMING_SOURCE_FILES})
