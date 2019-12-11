
#include "../../header/Network/AsyncServer.hh"

AsyncServer::AsyncServer() = default;

AsyncServer::~AsyncServer()
{
    if (m_netThread.joinable())
        m_netThread.join();
}

void AsyncServer::startServer()
{
    std::future<void> serverExitSignal = m_exitSignal.get_future();
    
    m_netThread = std::thread(&AsyncServer::serverLoop, this, std::move(serverExitSignal));
    m_netThread.detach();
}

void AsyncServer::stopServer()
{
    LogNetwork::logInfoMsg("Server stop...");
    exitAllClientConnection();
    exitConnection(m_srvSock);
    m_exitSignal.set_value();
}

ERR AsyncServer::initServer(const AsyncServer::__t_server_param &srvParam)
{
    m_srvParam = srvParam;
    if (initSocket() == NET_ERROR)
		return (NET_ERROR);
    if (bindSocket() == NET_ERROR)
        return (NET_ERROR);
    if (listenSocket() == NET_ERROR)
        return (NET_ERROR);
    m_lastSockAdded = m_srvSock;
	return (SUCCESS);
}

ERR AsyncServer::initSocket()
{
    int enable = 1;

    errno = 0;
    if ((m_srvSock = socket(m_srvParam.srv_ip_type, m_srvParam.srv_socket_type, m_srvParam.srv_protocol)) == NET_ERROR)
	{
		LogNetwork::logFailureMsg("Error on server socket initialization: " + errno);
		return (NET_ERROR);
	}
    setsockopt(m_srvSock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)); // allow kill
	LogNetwork::logSuccessMsg("Successfully initialize server socket: " + std::to_string(m_srvSock));
	return (SUCCESS);
}

ERR AsyncServer::bindSocket()
{
    errno = 0;
	memset(&m_srvSin, 0, sizeof(m_srvSin));
	m_srvSin.sin_family = m_srvParam.srv_ip_type;
	m_srvSin.sin_port = htons(m_srvParam.srv_port);
    m_srvSin.sin_addr.s_addr = m_srvParam.srv_ip_addr_cl;
    if ((bind(m_srvSock, (__sockaddr*)(&m_srvSin), sizeof(__sockaddr))) == NET_ERROR)
    {
        LogNetwork::logFailureMsg("Error bind failed: " + errno);
		return (NET_ERROR);
    }
    LogNetwork::logSuccessMsg("Successfully bind socket");
    return (SUCCESS);
}

ERR AsyncServer::listenSocket()
{
    errno = 0;
    if ((listen(m_srvSock, MAX_CLIENT)) == NET_ERROR)
    {
        LogNetwork::logFailureMsg("Error listen failed: " + errno);
		return (NET_ERROR);
    }
    LogNetwork::logSuccessMsg("Successfully listen socket");
    return (SUCCESS);
}

ERR AsyncServer::serverLoop(std::future<void> serverExitSignal)
{
    __timeval timeval;

    
    LogNetwork::logInfoMsg("Server start...");
    while (serverExitSignal.wait_for(std::chrono::milliseconds(UWAIT_STOP)) == std::future_status::timeout)
    {
        if (handleClient(&timeval) == NET_ERROR)
        {
            stopServer();
            return (NET_ERROR);
        }
    }
    stopServer();
    return (SUCCESS);
}

void AsyncServer::resetFdSet()
{
    __clients_iterator it = m_clients.begin();

    FD_ZERO(&m_readf);
    FD_SET(m_srvSock, &m_readf);
    for (; it != m_clients.end(); it++)
        FD_SET(it->second->getSock(), &m_readf);
}

ERR AsyncServer::handleClient(__timeval *timeval)
{
    errno = 0;
    resetFdSet();
    if (select((m_lastSockAdded + 1), &m_readf, NULL, NULL, timeval) == NET_ERROR)
    {
        LogNetwork::logFailureMsg("Error select failed: " + std::to_string(errno));
		return (NET_ERROR);
    }
    if (receiveNewConnection() == NET_ERROR)
        return (NET_ERROR);
    if (receiveDataFromClient() == NET_ERROR)
        return (NET_ERROR);
    if (eraseDecoClients() == NET_ERROR)
        return (NET_ERROR);
    return (SUCCESS);
}

bool AsyncServer::isDataOnSocket(__socket sock)
{
    return (FD_ISSET(sock, &m_readf));
}

ERR AsyncServer::acceptNewClient()
{
    __client_ptr newClient(new Client);
    __socket clientSock;
    __sockaddr_in clientSin;
    __sockaddr_in_size clientSinSize;
    static __client_id clientId = 0;

    errno = 0;
    clientSinSize = sizeof(clientSin);
    if ((clientSock = accept(m_srvSock, (__sockaddr*)(&clientSin), &clientSinSize)) == NET_ERROR)
	{
        LogNetwork::logFailureMsg("Error accept failed: " + std::to_string(errno));
		return (NET_ERROR);
    }
    newClient->setId(clientId++);
    newClient->setSock(clientSock);
    newClient->setSin(clientSin);
    newClient->setSinSize(clientSinSize);
    addNewClient(newClient);
    // update lastSockAdded to the last socket accepted
    m_lastSockAdded = (m_lastSockAdded > newClient->getSock()) ? m_lastSockAdded : newClient->getSock();
    LogNetwork::logInfoMsg("New client connection -> id: " + std::to_string(newClient->getId()));
    m_packetsManager.sendResponse(RESPONSE_SUCCESS, clientSock);
    return (SUCCESS);
}

void AsyncServer::addNewClient(__client_ptr client)
{
    m_clients.insert(std::make_pair(client->getId(), client));
    m_clientsNewForIa.push_back(client->getId());
}

ERR AsyncServer::receiveDataFromClient()
{
    std::string data;
    __clients_iterator it = m_clients.begin();

    for (; it != m_clients.end(); it++)
    {
        if (isDataOnSocket(it->second->getSock()))
        {
            if (readData(it->second) == NET_ERROR)
                return (NET_ERROR);
        }
    }
    return (SUCCESS);
}

void AsyncServer::addNewDataReceived(__client_ptr client, const std::string &data)
{
    m_mutex.lock();
    client->pushData(data);
    m_mutex.unlock();
}

ERR	AsyncServer::readData(__client_ptr client)
{
    ERR status;
    __t_packet packet;

    if ((status = m_packetsManager.receivePacket(client->getSock(), packet)) == NET_DECO)
    {
        exitConnection(client->getSock());
        addNewClientDeco(client->getId());
        return (SUCCESS);
    }
    else if (status == IGNORE_PACKET)
        return (SUCCESS);
    else if (status == NET_ERROR)
        return (NET_ERROR);
    client->pushData(packet.pk_data);
    #if (DEBUGNET_ACTIVE)
        LogNetwork::logInfoMsg("Packet completed !");
    #endif
	return (SUCCESS);
}

bool AsyncServer::isNewClientConnected()
{
    return (!m_clientsNewForIa.empty());
}

std::vector<__client_id> AsyncServer::getNewClientConnected()
{
    std::vector<__client_id> tmpVec = m_clientsNewForIa;
    
    m_clientsNewForIa.clear();
    return (tmpVec);
}

ERR AsyncServer::receiveNewConnection()
{
    if (isDataOnSocket(m_srvSock))
    {
        if (acceptNewClient() == NET_ERROR)
            return (NET_ERROR);
    }
    return (SUCCESS);
}

bool AsyncServer::isNewDataReceived(__client_id clientId)
{
    bool status = false;
     __clients_iterator it;

    if ((it = m_clients.find(clientId)) != m_clients.end())
        status = it->second->isData();
    return (status);
}

__data_vector AsyncServer::getNewDataReceived(__client_id clientId)
{
    __data_vector tmpVec;
    __clients_iterator it;

    if ((it = m_clients.find(clientId)) != m_clients.end())
    {
        tmpVec = it->second->getData();
        it->second->resetData();
    }
    return (tmpVec);
}

ERR AsyncServer::sendData(const std::string &data, __client_id clientId)
{
    __clients_iterator it;

    if ((it = m_clients.find(clientId)) == m_clients.end())
        return (NET_ERROR);
    if (m_packetsManager.sendResponse(data, it->second->getSock()) == NET_ERROR)
        return (NET_ERROR);
    return (SUCCESS);
}

bool AsyncServer::isSocketValid(__socket sock)
{
    __socket copyFd;
    
    errno = 0;
    copyFd = dup(sock);
    close(copyFd);
    return (!(errno == EBADF));
}

void AsyncServer::exitAllClientConnection()
{
    __clients_iterator it = m_clients.begin();

    for (; it != m_clients.end(); it++)
        exitConnection(it->second->getSock());
}

ERR AsyncServer::exitConnection(__socket sock)
{
    if (!isSocketValid(sock))
    {
        LogNetwork::logFailureMsg("Error: could not shutdown client connection");
        return (NET_ERROR);
    }
    shutdown(sock, SHUT_RDWR);
    close(sock);
    LogNetwork::logSuccessMsg("Successfully shutdown client connection");
    return (SUCCESS);
}

void AsyncServer::addNewClientDeco(__client_id clientId)
{
    m_clientsDecoToErase.push_back(clientId);
}

ERR AsyncServer::eraseDecoClients() 
{
    for (int id : m_clientsDecoToErase)
    {
        if (eraseClientById(id) == NET_ERROR)
            return (NET_ERROR);
    }
    m_clientsDecoToErase.clear();
    return (SUCCESS);
}

ERR AsyncServer::eraseClientById(__client_id clientId)
{
    __clients_iterator it;

    if ((it = m_clients.find(clientId)) == m_clients.end())
    {
        LogNetwork::logFailureMsg("Error could not erase client from map -> id: " + std::to_string(clientId));
        return (NET_ERROR);
    }
    m_clients.erase(it);
    LogNetwork::logSuccessMsg("Successfully erase client from map -> id: " + std::to_string(clientId));
    return (SUCCESS);
}