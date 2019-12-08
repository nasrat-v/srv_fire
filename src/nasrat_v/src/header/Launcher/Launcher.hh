//
// Created by nasrat_v on 3/7/19.
//

#ifndef OPENCV_SRV_LAUNCHER_HH
#define OPENCV_SRV_LAUNCHER_HH

#include "ProcessManager.hh"

class Launcher
{
public:
    Launcher(const DebugManager::debugMode &debugMode,
                        const ParamManager::paramMode &paramMode);
    ~Launcher();

    Error::ErrorType        launchAnalyse();
    Error::ErrorType        launchAnalyseNetwork();

private:
    DebugManager::debugMode m_debugMode;
    ParamManager::paramMode m_paramMode;
    ProcessManager          m_proccess;
};


#endif //OPENCV_SRV_LAUNCHER_HH
