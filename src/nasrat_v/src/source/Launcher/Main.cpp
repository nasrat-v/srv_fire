//
// Created by nasrat_v on 22/12/17.
//

#include "../../header/Launcher/DebugManager.hh"
#include "../../header/Launcher/ParamManager.hh"
#include "../../header/Launcher/Launcher.hh"

int runLauncher(const DebugManager::debugMode &debugMode,
                const ParamManager::paramMode &paramMode)
{
    Launcher launcher(debugMode, paramMode);

    if (paramMode & ParamManager::paramMode::NETWORK_MODE)
    {
        if (launcher.launchAnalyseNetwork() != Error::ErrorType::NOPE)
            return (1);
    }
    else
    {
        if (launcher.launchAnalyse() != Error::ErrorType::NOPE)
            return (1);
    }
    return (0);
}

int main(int ac, const char **av)
{
    ParamManager paramManager;
    ParamManager::paramMode paramMode;
    DebugManager debugManager;
    DebugManager::debugMode debugMode = DebugManager::debugMode::NO_DEBUG;

    if (ac > 1)
    {
        paramMode = paramManager.findParams(av);
        if (paramMode & ParamManager::paramMode::DEBUG_MODE)
            debugMode = debugManager.findDebugMode(av);
        if (runLauncher(debugMode, paramMode) == 1)
            return (1);
    }
    return (0);
}