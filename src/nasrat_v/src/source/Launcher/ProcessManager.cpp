
#include "../../header/Launcher/ProcessManager.hh"

ProcessManager::ProcessManager(const DebugManager::debugMode &debugMode,
                               const ParamManager::paramMode &paramMode) : m_debugMode(debugMode),
                                                                           m_paramMode(paramMode)
{
}

ProcessManager::~ProcessManager() = default;

Error::ErrorType ProcessManager::run()
{
    ProcessManager::__t_proc_event event;

    if (m_network.startAsyncNetwork() == NET_ERROR)
        return (Error::ErrorType::NETWORK);
    while (42)
    {
        while ((event = isEvent()).type == ProcessManager::pEventType::e_nothing)
        {
            std::this_thread::yield();
            usleep(1);
        }
        if (event.type == ProcessManager::pEventType::e_newClient)
        {
            if (handleNewClients() != Error::ErrorType::NOPE)
                return (Error::ErrorType::NETWORK);
        }
        else if (event.type == ProcessManager::pEventType::e_newDeco)
            handleNewDeco();
        else if (event.type == ProcessManager::pEventType::e_newData)
            handleNewDataReceived(event.client_id);
    }
    m_network.stopAsyncNetwork();
    return (Error::ErrorType::NOPE);
}

ProcessManager::__t_proc_event ProcessManager::isEvent()
{
    ProcessManager::__t_proc_event event;
    __process_map::iterator mapIt = m_processMap.begin();

    if (m_network.isNewClientConnected())
    {
        event.type = ProcessManager::pEventType::e_newClient;
        return (event);
    }
    if (m_network.isNewClientDeconnected())
    {
        event.type = ProcessManager::pEventType::e_newDeco;
        return (event);
    }
    for (; mapIt != m_processMap.end(); mapIt++)
    {
        if (m_network.isNewDataReceived(mapIt->first))
        {
            event.type = ProcessManager::pEventType::e_newData;
            event.client_id = mapIt->first;
            return (event);
        }
    }
    event.type = ProcessManager::pEventType::e_nothing;
    return (event);
}

Error::ErrorType ProcessManager::handleNewClients()
{
    std::vector<__client_id> newClients;

    newClients = m_network.getNewClientConnected();
    return (mapNewClients(newClients));
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
        new FrameAnalyser(m_debugMode, imgProvider, clientId, &displayWindowMainProcess)
    );

    if ((error = frameAnalyser->initAnalyser(false)) != Error::ErrorType::NOPE)
        return (error);
    m_processMap.insert(std::make_pair(clientId, imgProvider));
    m_analyseThread = std::thread(&FrameAnalyser::analyseFrame, frameAnalyser);
    m_analyseThread.detach();
    return (Error::ErrorType::NOPE);
}

void ProcessManager::handleNewDeco()
{
    std::vector<__client_id> clientsDeco;

    clientsDeco = m_network.getNewClientDeconnected();
    for (__client_id clientId : clientsDeco)
        terminateAnalyserProcess(clientId);
}

void ProcessManager::terminateAnalyserProcess(const __client_id &clientId)
{
    __process_map::iterator mapIt;

    if ((mapIt = m_processMap.find(clientId)) != m_processMap.end())
        mapIt->second->terminateAnalyserThread();
}

void ProcessManager::handleNewDataReceived(const __client_id &clientId)
{
    __process_map::iterator mapIt;

    if ((mapIt = m_processMap.find(clientId)) != m_processMap.end())
        sendDataToAnalyser(mapIt);
}

void ProcessManager::sendDataToAnalyser(const __process_map::iterator &mapIt)
{
    std::string path;
    __data_vector data;
    static size_t count = 0;

    data = m_network.getNewDataReceived(mapIt->first);
    for (__packet_data packet : data)
    {
        path = (PATH_RCV_FILE + std::to_string(mapIt->first) + "_file" 
                                            + std::to_string(count) + FORMAT_RCV_FILE);
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

void displayWindowMainProcess(__client_id clientId, const cv::Mat &img)
{
    //std::cout << "DISPLAY CALLBACK" << std::endl;
    cv::imshow(WINDOW_PREFIX + std::to_string(clientId), img);
    //cv::waitKey(0);
}