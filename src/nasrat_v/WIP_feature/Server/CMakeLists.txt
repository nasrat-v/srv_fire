
cmake_minimum_required(VERSION 3.9)
project(srv_fire)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -pthread")

set(SOURCE_FILES
	source/AsyncServer.cpp
	header/AsyncServer.hh
	source/Client.cpp
	header/Client.hh
	header/Packet.hh
	source/PacketsManager.cpp
	header/PacketsManager.hh
	source/NetworkManager.cpp
	header/NetworkManager.hh
	source/Log/LogNetwork.cpp
	header/Log/LogNetwork.hh
	source/Main.cpp)

add_executable(server_test ${SOURCE_FILES})
