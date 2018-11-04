//
// Created by nasrat_v on 11/4/18.
//

#ifndef OPENCV_SRV_DEBUGMODE_H
# define OPENCV_SRV_DEBUGMODE_H

# define THRESH_ARG             "--thresh"
# define CONTOUR_ARG            "--contour"
# define CONVEXHULLS_ARG        "--convexhulls"
# define ENTITIES_ARG           "--entities"
# define DIFFERENCE_ARG         "--difference"
# define TRACK_ARG              "--track"
# define NUMBER_ARG             "--number"
# define WATIKEY_ARG            "--waitkey"
# define OUTPUTPREDICTION_ARG   "--output-prediction"
# define NOORIGINALVIDEO_ARG    "--no-video"

#include <vector>
#include "output_static_object/Log.hh"

class DebugManager
{
public:
    DebugManager();
    ~DebugManager();

    Log::debugMode  findDebugMode(const char **av);

private:
    int                             strlenTab(const char **array);
    const std::vector<std::string>  convertCharStarToVectorOfString(const char **array);
};


#endif //OPENCV_SRV_DEBUGMODE_H
