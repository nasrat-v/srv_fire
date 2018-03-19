//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__
# define __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__

# define FILE_PATH  "/home/nasrat_v/Images/test_pattern.png"

#include <vector>
#include "ImageAnalyser.hh"
#include "Error.hh"

class BusinessLogicManager
{
public:
    BusinessLogicManager();
    ~BusinessLogicManager();

    void                run();

private:
    ImageAnalyser       _imageAnalyser;
};

#endif /* !__OPENCV_TEST_BUSINESSLOGICMANAGER_HH__ */
