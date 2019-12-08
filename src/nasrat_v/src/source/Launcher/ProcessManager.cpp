
#include "../../header/Launcher/ProcessManager.hh"

ProcessManager::ProcessManager(const DebugManager::debugMode &debugMode,
                               const ParamManager::paramMode &paramMode) : m_debugMode(debugMode),
                                                                           m_paramMode(paramMode)
{
}

ProcessManager::~ProcessManager() = default;

Error::ErrorType ProcessManager::run()
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
    m_analyseThread = std::thread(&FrameAnalyser::analyseFrame, frameAnalyser);
    m_analyseThread.detach();
    return (Error::ErrorType::NOPE);
}

void ProcessManager::handleNewDataReceived()
{
    __process_map::iterator mapIt = m_processMap.begin();

    for (; mapIt != m_processMap.end(); mapIt++)
    {
        if (m_network.isNewDataReceived(mapIt->first))
            sendDataToAnalyser(mapIt);
    }
}

void ProcessManager::sendDataToAnalyser(const __process_map::iterator &mapIt)
{
    std::string path;
    __data_vector data;
    static size_t count = 0;

    data = m_network.getNewDataReceived(mapIt->first);
    for (__packet_data packet : data)
    {
        path = (PATH_RCV_FILE + std::to_string(count) + FORMAT_RCV_FILE);
        createImageWithData(path, packet);
        mapIt->second->setImageNetworkPath(path);
        mapIt->second->setCanReadImage(true);
        count++;
    }
}

void ProcessManager::createImageWithData(const std::string &filePath, const __packet_data &packet)
{
    std::ofstream file;

    file.open(filePath);
    file << packet;
    file.close();
}