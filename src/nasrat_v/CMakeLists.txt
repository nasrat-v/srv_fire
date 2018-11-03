
cmake_minimum_required(VERSION 3.9)
project(opencv_srv)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -I /usr/include/opencv -L /usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lpthread")

set(SOURCE_FILES
        src/source/Main.cpp
        src/source/output_static_object/Error.cpp
        src/header/output_static_object/Error.hh
        src/source/output_static_object/Log.cpp
        src/header/output_static_object/Log.hh
        src/source/Entity.cpp
        src/header/Entity.h src/source/FrameSubstraction.cpp src/header/FrameSubstraction.h src/source/FrameAnalyser.cpp src/header/FrameAnalyser.h src/source/FrameAddition.cpp src/header/FrameAddition.h src/source/Frame.cpp src/header/Frame.h)

add_executable(opencv_srv ${SOURCE_FILES})