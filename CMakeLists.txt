cmake_minimum_required(VERSION 3.9)
project(srv_fire)
project(ia)

set(CMAKE_CXX_STANDARD 17)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_directories(/usr/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(srv_fire
        network/include/ANetwork.hpp
		main.cpp
        network/include/BusinessLogicManager.hh
        network/include/connectionHandler.h
        network/include/PacketHandler.h
        network/src/BusinessLogicManager.cpp
        network/src/connectionHandler.cpp
        network/src/PacketHandler.cpp
        network/src/CommandAnalyzer.cpp
        Utilitary/loger.hpp
        network/src/ProtocolManager.cpp
        Utilitary/sources/ClientNetwork.cpp
        Utilitary/sources/Error.cpp
        Utilitary/sources/LogNetwork.cpp
        Utilitary/sources/Log.cpp)

add_executable(ia
        imageAnalyzing/src/source/Launcher/Main.cpp
        imageAnalyzing/src/source/Log/Error.cpp
        imageAnalyzing/src/header/Log/Error.hh
        imageAnalyzing/src/source/Log/Log.cpp
        imageAnalyzing/src/header/Log/Log.hh
        imageAnalyzing/src/source/Analyser/Entity.cpp
        imageAnalyzing/src/header/Analyser/Entity.hh
        imageAnalyzing/src/source/Analyser/ImageProcesser.cpp
        imageAnalyzing/src/header/Analyser/ImageProcesser.hh
        imageAnalyzing/src/source/Analyser/FrameAnalyser.cpp
        imageAnalyzing/src/header/Analyser/FrameAnalyser.hh
        imageAnalyzing/src/source/Analyser/ImageAdditionner.cpp
        imageAnalyzing/src/header/Analyser/ImageAdditionner.hh
        imageAnalyzing/src/source/Analyser/Frame.cpp
        imageAnalyzing/src/header/Analyser/Frame.hh
        imageAnalyzing/src/source/Launcher/DebugManager.cpp
        imageAnalyzing/src/header/Launcher/DebugManager.hh
        imageAnalyzing/src/source/Analyser/ImageProvider.cpp
        imageAnalyzing/src/header/Analyser/ImageProvider.hh
        imageAnalyzing/src/source/Analyser/ImageService.cpp
        imageAnalyzing/src/header/Analyser/ImageService.hh
        imageAnalyzing/src/source/Analyser/Blob.cpp
        imageAnalyzing/src/header/Analyser/Blob.hh
        imageAnalyzing/src/source/Analyser/BlobFilter.cpp
        imageAnalyzing/src/header/Analyser/BlobFilter.hh
        imageAnalyzing/src/source/Analyser/EntityFilter.cpp
        imageAnalyzing/src/header/Analyser/EntityFilter.hh
        imageAnalyzing/src/source/Network/ClientNetwork.cpp
        imageAnalyzing/src/header/Network/ClientNetwork.hh
        imageAnalyzing/src/source/Network/Log/LogNetwork.cpp
        imageAnalyzing/src/header/Network/Log/LogNetwork.hh
        imageAnalyzing/src/source/Network/ProcessCommunication.cpp
        imageAnalyzing/src/header/Network/ProcessCommunication.hh
        imageAnalyzing/src/source/Launcher/ParamManager.cpp
        imageAnalyzing/src/header/Launcher/ParamManager.hh
        imageAnalyzing/src/source/Launcher/Launcher.cpp
        imageAnalyzing/src/header/Launcher/Launcher.hh)

target_link_libraries(srv_fire -pthread -lcurl -lcurlpp -L /usr/local/lib -L /usr/lib)

target_link_libraries(ia -I /usr/local/Cellar/opencv/3.4.3/include/opencv -L /usr/local/Cellar/opencv/3.4.3/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs)
