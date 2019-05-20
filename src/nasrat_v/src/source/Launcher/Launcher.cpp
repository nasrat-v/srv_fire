//
// Created by nasrat_v on 3/7/19.
//

#include "../../header/Launcher/Launcher.hh"

Launcher::Launcher() = default;

Launcher::~Launcher() = default;

Error::ErrorType Launcher::launchAnalyse(const DebugManager::debugMode &debugMode,
                                        const ParamManager::paramMode &paramMode)
{
    Error::ErrorType error;
    ImageProvider imageProvider(VIDEO_PATH, debugMode, paramMode);
    FrameAnalyser core(debugMode, &imageProvider);

    if ((error = core.initAnalyser(true)) != Error::ErrorType::NO_ERROR)
        return (error);
    return (core.analyseFrame());
}

Error::ErrorType Launcher::launchAnalyseNetwork(const DebugManager::debugMode &debugMode,
                                        const ParamManager::paramMode &paramMode,
                                        const std::string &idNetwork)
{
    Error::ErrorType error;
    ImageProvider imageProvider(VIDEO_PATH, debugMode, paramMode);
    FrameAnalyser core(debugMode, &imageProvider);

    if (launchThreadNetwork(idNetwork, &imageProvider, (debugMode & DebugManager::LOG_NETWORK)) == NET_ERROR)
        return (Error::ErrorType::THREAD_ERROR);
    if ((error = core.initAnalyser(false)) != Error::ErrorType::NO_ERROR)
        return (error);
    return (core.analyseFrame());
}

ERR Launcher::launchThreadNetwork(const std::string &idNetwork, ImageProvider *imageProvider, bool log)
{
    if (_processComm.initClient(log) == NET_ERROR)
        return (NET_ERROR);
    _processComm.startThread(idNetwork, imageProvider);
    return (SUCCESS);
}