//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__
# define __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__

# define DIR_PATH   "../input/image/"

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
    /* Methods */
    void                analyseAllFiles();
    void                analyse(const std::string &file_path);
};

#endif /* !__OPENCV_TEST_BUSINESSLOGICMANAGER_HH__ */
