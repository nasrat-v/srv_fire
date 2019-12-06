//
// Created by nasrat_v on 3/7/19.
//

#include "../../header/Launcher/Launcher.hh"

Launcher::Launcher() = default;

Launcher::~Launcher() = default;

Error::ErrorType Launcher::launchAnalyse(const DebugManager::debugMode &debugMode)
{
    Error::ErrorType error;
    FrameAnalyser analyser(debugMode);

    if ((error = analyser.initAnalyser(true)) != Error::ErrorType::NO_ERROR)
        return (error);
    return (analyser.analyseFrame());
}

Error::ErrorType Launcher::launchAnalyseNetwork(const DebugManager::debugMode &debugMode)
{
    m_proccess.run(debugMode);
}