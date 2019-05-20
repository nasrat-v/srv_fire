//
// Created by nasrat_v on 3/7/19.
//

#ifndef OPENCV_SRV_LAUNCHER_HH
#define OPENCV_SRV_LAUNCHER_HH

#include "../Analyser/FrameAnalyser.hh"
#include "../Network/ProcessCommunication.hh"

class Launcher
{
public:
    Launcher();
    ~Launcher();

    Error::ErrorType        launchAnalyse(const DebugManager::debugMode &debugMode,
                                            const ParamManager::paramMode &paramMode);
    Error::ErrorType        launchAnalyseNetwork(const DebugManager::debugMode &debugMode,
                                                const ParamManager::paramMode &paramMode,
                                                const std::string &idNetwork);
private:
    /* Attributes */
    ProcessCommunication    _processComm;

    /* Methods */
    ERR                     launchThreadNetwork(const std::string &idNetwork,
                                                ImageProvider *imageProvider, bool log);
};


#endif //OPENCV_SRV_LAUNCHER_HH
