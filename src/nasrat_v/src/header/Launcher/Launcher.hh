//
// Created by nasrat_v on 3/7/19.
//

#ifndef OPENCV_SRV_LAUNCHER_HH
#define OPENCV_SRV_LAUNCHER_HH

#include "ProcessManager.hh"

class Launcher
{
public:
    Launcher();
    ~Launcher();

    Error::ErrorType        launchAnalyse(const DebugManager::debugMode &debugMode);
    Error::ErrorType        launchAnalyseNetwork(const DebugManager::debugMode &debugMode);

private:
    ProcessManager          m_proccess;
};


#endif //OPENCV_SRV_LAUNCHER_HH
