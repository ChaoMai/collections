set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/src/factory_method FACTORY_METHOD_SOURCE_FILES)
add_executable(factory_method ${FACTORY_METHOD_SOURCE_FILES})
