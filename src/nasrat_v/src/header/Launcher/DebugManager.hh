//
// Created by nasrat_v on 11/4/18.
//

#ifndef OPENCV_SRV_DEBUGMODE_H
# define OPENCV_SRV_DEBUGMODE_H

# define THRESH_ARG             "--thresh"
# define CONTOUR_ARG            "--contours"
# define CONVEXHULLS_ARG        "--convexhulls"
# define SAVEDBLOBS_ARG         "--saved-blobs"
# define FRAMEFILTRATEBLOBS_ARG "--frame-filtrate-blobs"
# define DIFFERENCE_ARG         "--difference"
# define TRACK_ARG              "--track"
# define NUMBER_ARG             "--number"
# define WATIKEY_ARG            "--waitkey"
# define WEBCAM_ARG             "--webcam"
# define NOORIGINALVIDEO_ARG    "--no-video"
# define HOTSPOT_ARG            "--hot-spot"
# define PALETTE_ARG            "--palette"
# define SUBSTRACTCOLOR_ARG     "--substract-color"
# define SRCASIMG_ARG           "--src-as-img"
# define CREATESAMPLEIMG_ARG    "--create-sample-img"
# define LOGNETWORK_ARG         "--log-network"
# define HUEMAX                 179
# define SATMAX                 255
# define VALMAX                 255

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstring>
#include "stdio.h"

class DebugManager
{
public:
    DebugManager();
    ~DebugManager();

    enum    debugMode
    {
        NO_DEBUG = 0b0000'0000'0000'0000,
        WEBCAM = 0b0000'0000'0000'0001,
        THRESH = 0b0000'0000'0000'0010,
        CONTOUR = 0b0000'0000'0000'0100,
        CONVEXHULLS = 0b0000'0000'0000'1000,
        SAVED_BLOBS = 0b0000'0000'0001'0000,
        FRAME_FILTRATE_BLOBS = 0b0000'0000'0010'0000,
        DIFFERENCE = 0b0000'0000'0100'0000,
        TRACK = 0b0000'0000'1000'0000,
        NUMBER = 0b0000'0001'0000'0000,
        WAIT_KEY = 0b0000'0010'0000'0000,
        NO_ORIGINAL_VIDEO = 0b0000'0100'0000'0000,
        HOT_SPOT = 0b0000'1000'0000'0000,
        SUBSTRACT_COLOR = 0b0001'0000'0000'0000,
        SRC_AS_IMG = 0b0010'0000'0000'0000,
        CREATE_SAMPLE_IMG = 0b0100'0000'0000'0000,
        LOG_NETWORK = 0b1000'0000'0000'0000,
        ALL = 0b1111'1011'1111'1111
    };

    debugMode  findDebugMode(const char **av);

private:
    int                             strlenTab(const char **array);
    const std::vector<std::string>  convertCharStarToVectorOfString(const char **array);
};


#endif //OPENCV_SRV_DEBUGMODE_H
