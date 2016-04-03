set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/src/simple_factory SIMPLE_FACTORY_SOURCE_FILES)
add_executable(simple_factory ${SIMPLE_FACTORY_SOURCE_FILES})
