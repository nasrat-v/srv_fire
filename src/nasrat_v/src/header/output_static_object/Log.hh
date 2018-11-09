//
// Created by nasrat_v on 29/05/18.
//

#ifndef __OPENCV_SRV_LOG_HH__
# define __OPENCV_SRV_LOG_HH__

# define LOGFILE_PATH   "../output/log/log.txt"

#include <iostream>
#include <fstream>
#include <chrono>

class Log
{
public:
    static void                 logSomething(const std::string &complementary_msg = "", const std::string &file_path = LOGFILE_PATH, bool error = false);

    enum    debugMode
    {
        NO_DEBUG = 0b0000'0000'0000'0000,
        OUTPUT_PREDICTION = 0b0000'0000'0000'0001,
        THRESH = 0b0000'0000'0000'0010,
        CONTOUR = 0b0000'0000'0000'0100,
        CONVEXHULLS = 0b0000'0000'0000'1000,
        SAVED_ENTITIES = 0b0000'0000'0001'0000,
        FRAME_ENTITIES = 0b0000'0000'0010'0000,
        DIFFERENCE = 0b0000'0000'0100'0000,
        TRACK = 0b0000'0000'1000'0000,
        NUMBER = 0b0000'0001'0000'0000,
        WAIT_KEY = 0b0000'0010'0000'0000,
        NO_ORIGINAL_VIDEO = 0b0000'0100'0000'0000,
        HSV_PALETTE = 0b0000'1000'0000'0000,
        ALL = 0b1111'1011'1111'1111
    };

private:
    Log();
    ~Log();
    static const std::string    getTime();
};

#endif /* !__OPENCV_SRV_LOG_HH__ */
