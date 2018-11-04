//
// Created by nasrat_v on 22/12/17.
//

#include "../header/FrameAnalyser.h"
#include "../header/DebugManager.h"

int         main(int ac, const char **av)
{
    FrameAnalyser core;
    DebugManager debugManager;
    Log::debugMode mode = Log::debugMode::NO_DEBUG;

    if (ac > 1)
    {
        if (strncmp("--debug", av[1], strlen("--debug")) == 0)
            mode = debugManager.findDebugMode(av);
    }
    core.initAnalyser("../video/video_test_camp_fire.mp4", mode);
    if (core.analyseFrame() != 0)
    {
        Error::logError(Error::ErrorType::UNKNOWN_ERROR, "Something went wrong with the analyse");
        return (1);
    }
    return (0);
}
