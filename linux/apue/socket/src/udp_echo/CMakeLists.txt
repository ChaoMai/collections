set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(echo_udp_client client.cc)
add_executable(echo_udp_server server.cc)
