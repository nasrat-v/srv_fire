//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__
# define __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__

# define FILE_PATH  "/home/nasrat_v/Images/blue.jpg"

#include <vector>
#include "PacketHandler.h"
#include "ImageAnalyser.hh"
#include "Error.hh"
#include <thread>

class BusinessLogicManager
{
public:
    BusinessLogicManager(int Socket);
    ~BusinessLogicManager();

    void                run();

private:
    std::thread         _thread;
    PacketHandler       _network;
    ImageAnalyser       _imageAnalyser;
};

#endif /* !__OPENCV_TEST_BUSINESSLOGICMANAGER_HH__ */
