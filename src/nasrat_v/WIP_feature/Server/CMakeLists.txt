
cmake_minimum_required(VERSION 3.9)
project(srv_fire)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -pthread")

set(SOURCE_FILES
    source/ServerNetwork.cpp
	header/ServerNetwork.hh
	source/ProcessCommunication.cpp
	header/ProcessCommunication.hh
	source/Log/LogNetwork.cpp
	header/Log/LogNetwork.hh

	source/Main.cpp)

add_executable(server_test ${SOURCE_FILES})
