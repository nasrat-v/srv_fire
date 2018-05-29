
cmake_minimum_required(VERSION 3.9)
project(opencv_srv)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wundef -Wpointer-arith -Wcast-align -Wcast-qual -Wunreachable-code -I /usr/include/opencv -L /usr/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lpthread")

set(SOURCE_FILES
        src/source/Main.cpp
        src/source/business_logic_layer/BusinessLogicManager.cpp
        src/header/business_logic_layer/BusinessLogicManager.hh
        src/source/output_static_object/Error.cpp
        src/header/output_static_object/Error.hh
        src/source/data_transfert_object/Image.cpp
        src/header/data_transfert_object/Image.hh
        src/source/business_logic_layer/ImageAnalyser.cpp
        src/header/business_logic_layer/ImageAnalyser.hh
        src/source/data_transfert_object/Packet.cpp
        src/header/data_transfert_object/Packet.hh
        src/source/data_transfert_object/Pixel.cpp
        src/header/data_transfert_object/Pixel.hh
        src/source/data_transfert_object/Request.cpp
        src/header/data_transfert_object/Request.hh
        src/source/data_transfert_object/Zone.cpp
        src/header/data_transfert_object/Zone.hh
        src/source/business_logic_layer/ZoneAnalyser.cpp
        src/header/business_logic_layer/ZoneAnalyser.hh
	src/source/output_static_object/Log.cpp
	src/header/output_static_object/Log.hh)

add_executable(opencv_srv ${SOURCE_FILES})
