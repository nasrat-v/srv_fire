//
// Created by nasrat_v on 3/7/19.
//

#include "../../header/Launcher/Launcher.hh"

Launcher::Launcher(const DebugManager::debugMode &debugMode,
                   const ParamManager::paramMode &paramMode) : m_debugMode(debugMode),
                                                               m_paramMode(paramMode),
                                                               m_proccess(debugMode, paramMode)
{
}

Launcher::~Launcher() = default;

Error::ErrorType Launcher::launchAnalyse()
{
    static size_t clientId = 0;
    Error::ErrorType error;
    __img_provider_ptr imageProvider(
        new ImageProvider(DEFAULT_VIDEO_PATH, m_debugMode, m_paramMode)
    );
    FrameAnalyser analyser(m_debugMode, imageProvider, clientId, &displayWindowMainProcess);

    if ((error = analyser.initAnalyser(true)) != Error::ErrorType::NOPE)
        return (error);
    return (analyser.analyseFrame());
}

Error::ErrorType Launcher::launchAnalyseNetwork()
{
    return (m_proccess.run());
}