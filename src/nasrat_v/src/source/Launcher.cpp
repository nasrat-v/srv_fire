//
// Created by nasrat_v on 3/7/19.
//

#include "../header/Launcher.hh"

Launcher::Launcher() = default;

Launcher::~Launcher() = default;

Error::ErrorType Launcher::launchAnalyse(const DebugManager::debugMode &debugMode,
                                        const ParamManager::paramMode &paramMode)
{
    Error::ErrorType error;
    ImageProvider imageProvider(VIDEO_PATH);
    FrameAnalyser core(debugMode, &imageProvider);

    imageProvider.setParamMode(paramMode);
    if ((error = core.initAnalyser(true)) != Error::ErrorType::NO_ERROR)
        return (error);
    return (core.analyseFrame());
}

Error::ErrorType Launcher::launchAnalyseNetwork(const DebugManager::debugMode &debugMode,
                                        const ParamManager::paramMode &paramMode,
                                        const std::string &idNetwork)
{
    Error::ErrorType error;
    ImageProvider imageProvider(VIDEO_PATH);
    FrameAnalyser core(debugMode, &imageProvider);

    imageProvider.setParamMode(paramMode);
    if (launchThreadNetwork(idNetwork, &imageProvider) == NET_ERROR)
        return (Error::ErrorType::THREAD_ERROR);
    if ((error = core.initAnalyser(false)) != Error::ErrorType::NO_ERROR)
        return (error);
    return (core.analyseFrame());
}

ERR Launcher::launchThreadNetwork(const std::string &idNetwork, ImageProvider *imageProvider)
{
    if (_processComm.initClient() == NET_ERROR)
        return (NET_ERROR);
    _processComm.startThread(idNetwork, imageProvider);
    return (SUCCESS);
}