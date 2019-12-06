
#ifndef __PROCESS_MANAGER_HH__
#define __PROCESS_MANAGER_HH__

#include "../Analyser/FrameAnalyser.hh"
#include "../Network/NetworkManager.hh"

class ProcessManager
{
public:
    ProcessManager();
    ~ProcessManager();

    Error::ErrorType    run(const DebugManager::debugMode &debugMode);

private:
    NetworkManager      m_network;

    ERR                 networkLoop();
};

#endif /* !__PROCESS_MANAGER_HH__ */