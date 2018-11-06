//
// Created by nasrat_v on 11/4/18.
//

#include <cstring>
#include "../header/DebugManager.h"

DebugManager::DebugManager() = default;

DebugManager::~DebugManager() = default;

const std::vector<std::string> DebugManager::convertCharStarToVectorOfString(const char **array)
{
    return (std::vector<std::string>(array, array + (strlenTab(array))));
}

int DebugManager::strlenTab(const char **array)
{
    int i = -1;

    while (array[++i]);
    return (i);
}

Log::debugMode DebugManager::findDebugMode(const char **av)
{
    uint16_t mode = Log::debugMode::NO_DEBUG;
    std::vector<std::string> args = convertCharStarToVectorOfString(av);
    std::vector<std::string>::const_iterator it = args.begin();

    if (args.size() == 2)
        return (Log::debugMode::ALL);
    it++;
    while (it != args.end())
    {
        if (*it == THRESH_ARG)
            mode |= Log::debugMode::THRESH;
        if (*it == CONTOUR_ARG)
            mode |= Log::debugMode::CONTOUR;
        if (*it == CONVEXHULLS_ARG)
            mode |= Log::debugMode::CONVEXHULLS;
        if (*it == SAVEDENTITIES_ARG)
            mode |= Log::debugMode::SAVED_ENTITIES;
        if (*it == FRAMEENTITIES_ARG)
            mode |= Log::debugMode::FRAME_ENTITIES;
        if (*it == DIFFERENCE_ARG)
            mode |= Log::debugMode::DIFFERENCE;
        if (*it == TRACK_ARG)
            mode |= Log::debugMode::TRACK;
        if (*it == NUMBER_ARG)
            mode |= Log::debugMode::NUMBER;
        if (*it == WATIKEY_ARG)
            mode |= Log::debugMode::WAIT_KEY;
        if (*it == OUTPUTPREDICTION_ARG)
            mode |= Log::debugMode::OUTPUT_PREDICTION;
        if (*it == NOORIGINALVIDEO_ARG)
            mode |= Log::debugMode::NO_ORIGINAL_VIDEO;
        it++;
    }
    return ((Log::debugMode)mode);
}
