set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(tldp_echo_client simple_client_main.cpp ClientSocket.cpp
  Socket.cpp)
add_executable(tldp_echo_server simple_server_main.cpp ServerSocket.cpp
  Socket.cpp)
