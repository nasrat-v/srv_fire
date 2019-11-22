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
    srvParam._ip_type = AF_INET;
    srvParam._socket_type = SOCK_STREAM;
    srvParam._protocol = IPPROTO_TCP;
    srvParam._ip_addr_client = INADDR_ANY;
    srvParam._port = PORT;
    return (srvParam);
}

ERR ProcessCommunication::communicateWithServer()
{
    std::ofstream file;
    static int count = 0;
    ServerNetwork::t_clientData data;

    if (initServer() == NET_ERROR)
        return (NET_ERROR);
    _network.startServer();
    while (42)
    {
        if (_network.isNewDataReceived())
        {
            file.open (PATH_RCV_FILE + std::to_string(count) + FORMAT_RCV_FILE);
            data = _network.getLastDataReceived();
            std::cout << "[Received from " << data._client_id << "]: " << data._data << std::endl;
            file << data._data;
            file.close();
            count++;
        }
    }
    _network.stopServer();
    return (SUCCESS);
}