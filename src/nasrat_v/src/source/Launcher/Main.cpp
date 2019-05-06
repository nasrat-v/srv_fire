//
// Created by nasrat_v on 22/12/17.
//

#include "../../header/Launcher/DebugManager.hh"
#include "../../header/Launcher/ParamManager.hh"
#include "../../header/Launcher/Launcher.hh"

int main(int ac, const char **av)
{
    ParamManager paramManager;
    ParamManager::paramMode paramMode;
    DebugManager debugManager;
    DebugManager::debugMode debugMode = DebugManager::debugMode::NO_DEBUG;
    Launcher launcher;

    if (ac > 1)
    {
        paramMode = paramManager.findParams(av);
        if (paramMode & ParamManager::paramMode::DEBUG_MODE)
            debugMode = debugManager.findDebugMode(av);
        if (paramMode & ParamManager::paramMode::NETWORK_MODE)
        {
            if (launcher.launchAnalyseNetwork(debugMode, paramMode,
                    paramManager.getIdNetwork()) != Error::ErrorType::NO_ERROR)
                return (1);
        }
        else
        {
            if (launcher.launchAnalyse(debugMode, paramMode) != Error::ErrorType::NO_ERROR)
                return (1);
        }
    }
    return (0);
}