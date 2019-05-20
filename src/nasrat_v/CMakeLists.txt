
cmake_minimum_required(VERSION 3.9)
project(opencv_srv)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -I /usr/include/opencv -L /usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -pthread")

set(SOURCE_FILES
        src/source/Launcher/Main.cpp
        src/source/Log/Error.cpp
        src/header/Log/Error.hh
        src/source/Log/Log.cpp
        src/header/Log/Log.hh
        src/source/Analyser/Blob.cpp
        src/header/Analyser/Blob.hh
        src/source/Analyser/ImageProcesser.cpp
        src/header/Analyser/ImageProcesser.hh
        src/source/Analyser/FrameAnalyser.cpp
        src/header/Analyser/FrameAnalyser.hh
        src/source/Analyser/ImageAdditionner.cpp
        src/header/Analyser/ImageAdditionner.hh
        src/source/Analyser/Frame.cpp
        src/header/Analyser/Frame.hh
        src/source/Launcher/DebugManager.cpp
        src/header/Launcher/DebugManager.hh
        src/source/Analyser/ImageProvider.cpp
        src/header/Analyser/ImageProvider.hh
        src/source/Analyser/ImageService.cpp
        src/header/Analyser/ImageService.hh
        src/source/Network/ClientNetwork.cpp
        src/header/Network/ClientNetwork.hh
        src/source/Network/Log/LogNetwork.cpp
        src/header/Network/Log/LogNetwork.hh
        src/source/Network/ProcessCommunication.cpp
        src/header/Network/ProcessCommunication.hh
        src/source/Launcher/ParamManager.cpp
        src/header/Launcher/ParamManager.hh
        src/source/Launcher/Launcher.cpp
        src/header/Launcher/Launcher.hh
        src/source/Analyser/Entity.cpp
        src/header/Analyser/Entity.hh
        src/header/Analyser/ScalarColor.hpp
        src/header/Analyser/BlobFilter.hh
        src/source/Analyser/BlobFilter.cpp
        src/header/Analyser/EntityFilter.hh
        src/source/Analyser/EntityFilter.cpp src/header/Analyser/IdManager.hpp)

add_executable(opencv_srv ${SOURCE_FILES})