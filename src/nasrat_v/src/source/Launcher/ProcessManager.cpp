
#include "../../header/Launcher/ProcessManager.hh"

ProcessManager::ProcessManager(const DebugManager::debugMode &debugMode,
                               const ParamManager::paramMode &paramMode) : m_debugMode(debugMode),
                                                                           m_paramMode(paramMode)
{
}

ProcessManager::~ProcessManager() = default;

Error::ErrorType ProcessManager::run()
{
}

Error::ErrorType ProcessManager::handleNewClients()
{
    std::vector<__client_id> newClients;

    if (m_network.isNewClientConnected())
    {
        newClients = m_network.getNewClientConnected();
        return (mapNewClients(newClients));
    }
    return (Error::ErrorType::NOPE);
}

Error::ErrorType ProcessManager::mapNewClients(const __client_id_vector &clients)
{
    Error::ErrorType error;

    for (__client_id clientId : clients)
    {
        if ((error = linkClientToAnalyser(clientId)) != Error::ErrorType::NOPE)
            return (error);
    }
    return (Error::ErrorType::NOPE);
}

Error::ErrorType ProcessManager::linkClientToAnalyser(__client_id clientId)
{
    Error::ErrorType error;
    __img_provider_ptr imgProvider(
        new ImageProvider(DEFAULT_VIDEO_PATH, m_debugMode, m_paramMode)
    );
    __frame_analyser_ptr frameAnalyser(
        new FrameAnalyser(m_debugMode, imgProvider)
    );

    if ((error = frameAnalyser->initAnalyser(false)) != Error::ErrorType::NOPE)
        return (error);
    m_processMap.insert(std::make_pair(clientId, imgProvider));
    std::thread(&FrameAnalyser::analyseFrame, frameAnalyser);
}

void ProcessManager::handleNewDataReceived()
{
    __process_map::iterator mapIt = m_processMap.begin();

    for (; mapIt != m_processMap.end(); mapIt++)
    {
        if (m_network.isNewDataReceived(mapIt->first))
            sendDataToAnalyser(mapIt->first);
    }
}

void ProcessManager::sendDataToAnalyser(__client_id clientId)
{
    std::ofstream file;
    static size_t count = 0;
    __data_vector data;
    __process_map::iterator mapIt;

    data = m_network.getNewDataReceived(clientId);
    if ((mapIt = m_processMap.find(clientId)) != m_processMap.end())
    {
        file.open(""); //create file
        mapIt->second->setImageNetworkPath();
        mapIt->second->setCanReadImage(true);
    }
}

Error::ErrorType ProcessManager::networkLoop()
{
    if (m_network.startAsyncNetwork() == NET_ERROR)
        return (Error::ErrorType::NETWORK);
    while (42)
    {
        if (handleNewClients() != Error::ErrorType::NOPE)
            return (Error::ErrorType::NETWORK);
        handleNewDataReceived();
        usleep(1);
    }
    m_network.stopAsyncNetwork();
    return (Error::ErrorType::NOPE);
}