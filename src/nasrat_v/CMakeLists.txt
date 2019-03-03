
cmake_minimum_required(VERSION 3.9)
project(opencv_srv)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -I /usr/include/opencv -L /usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lpthread")

set(SOURCE_FILES
        src/source/Main.cpp
        src/source/Log/Error.cpp
        src/header/Log/Error.hh
        src/source/Log/Log.cpp
        src/header/Log/Log.hh
        src/source/Entity.cpp
        src/header/Entity.h
        src/source/ImageProcesser.cpp
        src/header/ImageProcesser.h
        src/source/FrameAnalyser.cpp
        src/header/FrameAnalyser.h
        src/source/ImageAdditionner.cpp
        src/header/ImageAdditionner.h
        src/source/Frame.cpp
        src/header/Frame.h
        src/source/DebugManager.cpp
        src/header/DebugManager.h
        src/source/ImageProvider.cpp
        src/header/ImageProvider.h
        src/source/ImageService.cpp
        src/header/ImageService.h
        src/source/ConfigManager.cpp
        src/header/ConfigManager.h
        src/source/Network/ClientNetwork.cpp
        src/header/Network/ClientNetwork.hh
        src/source/Network/Log/LogNetwork.cpp
        src/header/Network/Log/LogNetwork.hh src/source/Network/ProcessCommunication.cpp src/header/Network/ProcessCommunication.hh)

add_executable(opencv_srv ${SOURCE_FILES})