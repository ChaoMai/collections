set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/src)

aux_source_directory(${PROJECT_SOURCE_DIR}/src/ch14 CH14_SOURCE_FILES)
add_executable(ch14 ${CH14_SOURCE_FILES})
