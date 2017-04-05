# Install script for directory: /Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch02/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch03/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch05/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch07/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch08/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch09/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch10/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch11/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch12/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch13/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch14/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch15/cmake_install.cmake")
  include("/Users/chaomai/Documents/codes/github/learning/cpp_learning/cpp_primer/build/src/ch16/cmake_install.cmake")

endif()

