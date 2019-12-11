
#ifndef __PROCESS_MANAGER_HH__
#define __PROCESS_MANAGER_HH__

# define PATH_RCV_FILE      "../output/image/client"
# define FORMAT_RCV_FILE    ".png"

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

    enum class  pEventType
    {
        e_newClient,
        e_newData,
        e_nothing
    };

    typedef struct      __s_proc_event
    {
        pEventType      type;
        __client_id     client_id;
    }                   __t_proc_event;

    Error::ErrorType    run();
    Error::ErrorType    launchAnalyse();

private:
    NetworkManager          m_network;
    __process_map           m_processMap;
    DebugManager::debugMode m_debugMode;
    ParamManager::paramMode m_paramMode;
    std::thread             m_analyseThread;

    Error::ErrorType    networkLoop();
    __t_proc_event      isEvent();
    Error::ErrorType    handleNewClients();
    Error::ErrorType    mapNewClients(const __client_id_vector &clients);
    Error::ErrorType    linkClientToAnalyser(__client_id clientId);
    void                handleNewDataReceived(const __client_id &clientId);
    void                sendDataToAnalyser(const __process_map::iterator &mapIt);
    void                createImageWithData(const std::string &filePath, 
                                                const __packet_data &packet);
};

#endif /* !__PROCESS_MANAGER_HH__ */