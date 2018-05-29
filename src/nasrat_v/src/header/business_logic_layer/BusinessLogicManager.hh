//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__
# define __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__

#include <vector>
#include "dirent.h"
#include "ImageAnalyser.hh"

class BusinessLogicManager
{
public:
    BusinessLogicManager();
    ~BusinessLogicManager();

    void                run();

private:
    ImageAnalyser       _imageAnalyser;
    ImageAnalyser       _imageAnalyser2;
};

#endif /* !__OPENCV_TEST_BUSINESSLOGICMANAGER_HH__ */
