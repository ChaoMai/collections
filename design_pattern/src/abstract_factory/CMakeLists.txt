set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/src/abstract_factory ABSTRACT_FACTORY_SOURCE_FILES)
add_executable(abstract_factory ${ABSTRACT_FACTORY_SOURCE_FILES})
