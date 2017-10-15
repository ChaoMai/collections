set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include_directories(/usr/local/include/)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(leveldb STATIC IMPORTED)
set_property(TARGET leveldb PROPERTY IMPORTED_LOCATION /usr/local/lib/libleveldb.a)

add_library(snappy STATIC IMPORTED)
set_property(TARGET snappy PROPERTY IMPORTED_LOCATION /usr/local/lib/libsnappy.a)

add_executable(db_test ${PROJECT_SOURCE_DIR}/src/main.cc)

target_link_libraries(db_test leveldb snappy)