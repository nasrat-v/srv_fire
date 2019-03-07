
cmake_minimum_required(VERSION 3.9)
project(opencv_srv)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -I /usr/include/opencv -L /usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -pthread")

set(SOURCE_FILES
        src/source/Main.cpp
        src/source/Log/Error.cpp
        src/header/Log/Error.hh
        src/source/Log/Log.cpp
        src/header/Log/Log.hh
        src/source/Entity.cpp
        src/header/Entity.hh
        src/source/ImageProcesser.cpp
        src/header/ImageProcesser.hh
        src/source/FrameAnalyser.cpp
        src/header/FrameAnalyser.hh
        src/source/ImageAdditionner.cpp
        src/header/ImageAdditionner.hh
        src/source/Frame.cpp
        src/header/Frame.hh
        src/source/DebugManager.cpp
        src/header/DebugManager.hh
        src/source/ImageProvider.cpp
        src/header/ImageProvider.hh
        src/source/ImageService.cpp
        src/header/ImageService.hh
        src/source/Network/ClientNetwork.cpp
        src/header/Network/ClientNetwork.hh
        src/source/Network/Log/LogNetwork.cpp
        src/header/Network/Log/LogNetwork.hh
        src/source/Network/ProcessCommunication.cpp
        src/header/Network/ProcessCommunication.hh
        src/source/ParamManager.cpp src/header/ParamManager.hh src/source/Launcher.cpp src/header/Launcher.hh)

add_executable(opencv_srv ${SOURCE_FILES})