//
// Created by nasrat_v on 3/3/19.
//

#include "../../header/Network/ProcessCommunication.hh"

ProcessCommunication::ProcessCommunication() = default;

ProcessCommunication::~ProcessCommunication()
{
    if(_netThread.joinable())
        _netThread.join();
}

ERR ProcessCommunication::initClient()
{
    ClientNetwork::t_serverParam srvParam;

    srvParam = initConfigurationServer();
    if (_network.initNetworkClient(srvParam) == NET_ERROR)
    {
        LogNetwork::logFailureMsg("Config error with server at " +
                           std::string(srvParam.hostName) + ":" + std::to_string(srvParam.port));
        return (NET_ERROR);
    }
    return (SUCCESS);
}

const ClientNetwork::t_serverParam ProcessCommunication::initConfigurationServer()
{
    ClientNetwork::t_serverParam srvParam;

    memset(&srvParam, 0, sizeof(srvParam));
    srvParam.ipType = AF_INET;
    srvParam.socketType = SOCK_STREAM;
    srvParam.protocol = IPPROTO_TCP;
    srvParam.hostName = nullptr;
    srvParam.serviceName = nullptr;
    srvParam.ipAddr = IPADDR;
    srvParam.port = PORT;
    return (srvParam);
}

void ProcessCommunication::startThread(const std::string &idNetwork, ImageProvider *imageProvider)
{
    _netThread = std::thread(&ProcessCommunication::communicateWithServer, this, idNetwork, imageProvider);
    _netThread.detach();
}

ERR ProcessCommunication::communicateWithServer(const std::string &idNetwork, ImageProvider *imageProvider)
{
    std::string data;

    while (_network.connectToServer() == NET_ERROR)
    {
        std::this_thread::yield(); // TRY UNTIL IT CAN CONNECT => like sleep in infinite loop
    }
    std::cout << "Connected" << std::endl;
    if (sendJsonConnection(idNetwork) == NET_ERROR)
        return (NET_ERROR);
    while (_network.isConnected())
    {
        if (_network.isDataToRead())
        {
            _network.readData(data);
            formatData(data);
            _mutex.lock();
            imageProvider->setImageNetworkPath(data);
            imageProvider->setCanReadImage(true);
            _mutex.unlock();
            resetString(data);
        }
    }
    return (SUCCESS);
}

ERR ProcessCommunication::sendJsonConnection(const std::string &idNetwork)
{
    return (_network.writeData((JSON_ID + idNetwork + JSON_TYPE)));
}

void ProcessCommunication::resetString(std::string &str)
{
    str = "";
}

void ProcessCommunication::formatData(std::string &data)
{
    size_t pos = data.find('\n');

    data[pos] = '\0';
}
