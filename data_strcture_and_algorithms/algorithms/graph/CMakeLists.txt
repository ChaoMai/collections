set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/graph/src GRAPH_SOURCE_FILES)
add_executable(algorithms_graph ${GRAPH_SOURCE_FILES})
