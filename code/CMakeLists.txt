cmake_minimum_required(VERSION 3.10)
project(computer_science)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(include/)



add_executable(main src/main.cpp)
