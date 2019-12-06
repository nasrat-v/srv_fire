
#include "../../header/Network/NetworkManager.hh"

NetworkManager::NetworkManager() = default;

NetworkManager::~NetworkManager() = default;

ERR NetworkManager::initServer()
{
    AsyncServer::__t_server_param srvParam;

    srvParam = initConfigurationServer();
    if (m_server.initServer(srvParam) == NET_ERROR)
        return (NET_ERROR);
    return (SUCCESS);
}

const AsyncServer::__t_server_param NetworkManager::initConfigurationServer()
{
    AsyncServer::__t_server_param srvParam;

    memset(&srvParam, 0, sizeof(srvParam));
    srvParam.srv_ip_type = AF_INET;
    srvParam.srv_socket_type = SOCK_STREAM;
    srvParam.srv_protocol = IPPROTO_TCP;
    srvParam.srv_ip_addr_cl = INADDR_ANY;
    srvParam.srv_port = PORT;
    return (srvParam);
}

std::vector<__client_id> NetworkManager::getNewClientConnected()
{
    if (m_server.isNewClientConnected())
        return (m_server.getNewClientConnected());
    return (std::vector<__client_id>());
}

__data_vector NetworkManager::getNewDataReceived(__client_id clientId)
{
    if (m_server.isNewDataReceived(clientId))
        return (m_server.getNewDataReceived(clientId));
}

ERR NetworkManager::startAsyncNetwork()
{
    if (initServer() == NET_ERROR)
        return (NET_ERROR);
    m_server.startServer();
    return (SUCCESS);
}

void NetworkManager::stopAsyncNetwork()
{
    m_server.stopServer();
}