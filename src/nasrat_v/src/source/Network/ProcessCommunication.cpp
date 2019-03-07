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
        std::this_thread::yield(); // TRY UNTIL IT CAN CONNECT
    if (typeRequest() == NET_ERROR)
        return (NET_ERROR);
    if (idRequest(idNetwork) == NET_ERROR)
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

ERR ProcessCommunication::typeRequest()
{
    std::string data;

    _network.readData(data);
    if (data == TYPE_ASK)
    {
        if (_network.writeData(TYPE_RESP) == NET_ERROR)
            return (NET_ERROR);
    }
    return (SUCCESS);
}

ERR ProcessCommunication::idRequest(const std::string &idNetwork)
{
    std::string data;

    _network.readData(data);
    if (data == ID_ASK)
    {
        if (_network.writeData(idNetwork) == NET_ERROR)
            return (NET_ERROR);
    }
    return (SUCCESS);
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
