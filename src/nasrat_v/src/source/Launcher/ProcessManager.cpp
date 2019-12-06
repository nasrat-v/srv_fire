
#include "../../header/Launcher/ProcessManager.hh"

ProcessManager::ProcessManager() = default;

ProcessManager::~ProcessManager() = default;

Error::ErrorType ProcessManager::run(const DebugManager::debugMode &debugMode)
{
    Error::ErrorType error;
    FrameAnalyser analyser(debugMode);

    if ((error = analyser.initAnalyser(false)) != Error::ErrorType::NO_ERROR)
        return (error);
    return (analyser.analyseFrame());
}

ERR ProcessManager::networkLoop()
{
    std::ofstream file;
    static int count = 0;
    __data_vector data;
    std::vector<__client_id> newClients;

    if (m_network.startAsyncNetwork() == NET_ERROR)
        return (NET_ERROR);
    while (42)
    {
        if (!(newClients = m_network.getNewClientConnected()).empty())
        {
            // link new client to ia then launch thread ia
        }
        data = m_server.getNewDataReceived(0);
        for (__packet_data packet : data)
        {
            file.open(PATH_RCV_FILE + std::to_string(count) + FORMAT_RCV_FILE);
            file << packet;
            file.close();
            count++;
        }
        usleep(1);
    }
    m_server.stopServer();
    return (SUCCESS);
}
}