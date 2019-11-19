//
// Created by nasrat_v on 3/3/19.
//

#include "../header/ProcessCommunication.hh"

ProcessCommunication::ProcessCommunication() = default;

ProcessCommunication::~ProcessCommunication() = default;

ERR ProcessCommunication::initServer()
{
    ServerNetwork::t_serverParam srvParam;

    srvParam = initConfigurationServer();
    if (_network.initServer(srvParam) == NET_ERROR)
        return (NET_ERROR);
    return (SUCCESS);
}

const ServerNetwork::t_serverParam ProcessCommunication::initConfigurationServer()
{
    ServerNetwork::t_serverParam srvParam;

    memset(&srvParam, 0, sizeof(srvParam));
    srvParam.ipType = AF_INET;
    srvParam.socketType = SOCK_STREAM;
    srvParam.protocol = IPPROTO_TCP;
    srvParam.ipAddrClient = INADDR_ANY;
    srvParam.port = PORT;
    return (srvParam);
}

ERR ProcessCommunication::communicateWithServer()
{
    static int count = 0;
    ServerNetwork::t_clientData data;

    if (initServer() == NET_ERROR)
        return (NET_ERROR);
    _network.startServer();
    while (42)
    {
        if (_network.isNewDataReceived())
        {
            data = _network.getLastDataReceived();
            std::cout << "[Received from " << data.clientId << "]: " << data.data << std::endl;
            count++;
            _network.sendData("caca", data.clientId);
        }
        if (count == 3)
            break;
    }
    _network.stopServer();
    return (SUCCESS);
}