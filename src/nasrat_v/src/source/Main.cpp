//
// Created by nasrat_v on 22/12/17.
//

#include "../header/FrameAnalyser.h"
#include "../header/DebugManager.h"

Error::ErrorType analyse(const DebugManager::debugMode &mode)
{
    Error::ErrorType error;
    FrameAnalyser core(mode, VIDEO_PATH);

    if ((error = core.initAnalyser()) != Error::ErrorType::NO_ERROR)
        return (error);
    return (core.analyseFrame());
}

int         main(int ac, const char **av)
{
    DebugManager debugManager;
    DebugManager::debugMode mode = DebugManager::debugMode::NO_DEBUG;

    if (ac > 1)
    {
        if (strncmp("--debug", av[1], strlen("--debug")) == 0)
            mode = debugManager.findDebugMode(av);
    }
    if (analyse(mode) != Error::ErrorType::NO_ERROR)
        return (1);
    return (0);
}