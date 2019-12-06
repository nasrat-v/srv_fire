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
    Error::ErrorType error;
    __img_provider_ptr imageProvider(
        new ImageProvider(DEFAULT_VIDEO_PATH, m_debugMode, m_paramMode)
    );
    FrameAnalyser analyser(m_debugMode, imageProvider);

    if ((error = analyser.initAnalyser(true)) != Error::ErrorType::NOPE)
        return (error);
    return (analyser.analyseFrame());
}

Error::ErrorType Launcher::launchAnalyseNetwork()
{
    m_proccess.run();
}