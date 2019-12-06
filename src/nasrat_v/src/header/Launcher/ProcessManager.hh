
#ifndef __PROCESS_MANAGER_HH__
#define __PROCESS_MANAGER_HH__

#include "../Analyser/FrameAnalyser.hh"
#include "../Network/NetworkManager.hh"

typedef std::shared_ptr<ImageProvider>              __img_provider_ptr;
typedef std::shared_ptr<FrameAnalyser>              __frame_analyser_ptr;
typedef std::map<__client_id, __img_provider_ptr>   __process_map;

class ProcessManager
{
public:
    ProcessManager(const DebugManager::debugMode &debugMode,
                            const ParamManager::paramMode &paramMode);
    ~ProcessManager();

    Error::ErrorType    run();
    Error::ErrorType    launchAnalyse();

private:
    NetworkManager          m_network;
    __process_map           m_processMap;
    DebugManager::debugMode m_debugMode;
    ParamManager::paramMode m_paramMode;

    Error::ErrorType    networkLoop();
    Error::ErrorType    handleNewClients();
    Error::ErrorType    mapNewClients(const __client_id_vector &clients);
    Error::ErrorType    linkClientToAnalyser(__client_id clientId);
    void                handleNewDataReceived();
    void                sendDataToAnalyser(__client_id clientId);
};

#endif /* !__PROCESS_MANAGER_HH__ */