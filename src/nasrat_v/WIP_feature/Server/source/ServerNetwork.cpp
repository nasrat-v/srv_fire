
#include "../header/ServerNetwork.hh"

ServerNetwork::ServerNetwork() : m_packetsManager(m_freshPackets, m_processedPackets) {}

ServerNetwork::~ServerNetwork()
{
    if (m_netThread.joinable())
        m_netThread.join();
}

void ServerNetwork::startServer()
{
    std::future<void> serverExitSignal = m_exitSignal.get_future();
    
    m_netThread = std::thread(&ServerNetwork::serverLoop, this, std::move(serverExitSignal));
    m_netThread.detach();
}

void ServerNetwork::stopServer()
{
    LogNetwork::logInfoMsg("Server stop...");
    exitAllClientConnection();
    exitConnection(m_srvSock);
    m_exitSignal.set_value();
}

ERR ServerNetwork::initServer(const ServerNetwork::__t_server_param &srvParam)
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

ERR ServerNetwork::initSocket()
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

ERR ServerNetwork::bindSocket()
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

ERR ServerNetwork::listenSocket()
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

ERR ServerNetwork::serverLoop(std::future<void> serverExitSignal)
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

void ServerNetwork::resetFdSet()
{
    __clients_iterator it = m_clients.begin();

    FD_ZERO(&m_readf);
    FD_SET(m_srvSock, &m_readf);
    for (; it != m_clients.end(); it++)
        FD_SET(it->second->getSock(), &m_readf);
}

ERR ServerNetwork::handleClient(__timeval *timeval)
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

bool ServerNetwork::isDataOnSocket(__socket sock)
{
    return (FD_ISSET(sock, &m_readf));
}

ERR ServerNetwork::receiveNewConnection()
{
    if (isDataOnSocket(m_srvSock))
    {
        if (acceptNewClient() == NET_ERROR)
            return (NET_ERROR);
    }
    return (SUCCESS);
}

ERR ServerNetwork::acceptNewClient()
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
    return (SUCCESS);
}

void ServerNetwork::addNewClient(__client_ptr client)
{
    m_clients.insert(std::make_pair(client->getId(), client));
}

ERR ServerNetwork::receiveDataFromClient()
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

void ServerNetwork::addNewDataReceived(__client_ptr client, const std::string &data)
{
    m_mutex.lock();
    client->pushData(data);
    // -------------->> add type enum UNKNOWN to packet when create
    m_mutex.unlock();
}

ERR	ServerNetwork::readData(__client_ptr client)
{
    __ret ret;
	char buff[(SIZE_BUFF + sizeof(char))] = { 0 };

    errno = 0;
	if ((ret = read(client->getSock(), buff, SIZE_BUFF)) > 0)
		addNewDataReceived(client, buff);
	else if (ret < 0)
	{
		LogNetwork::logFailureMsg("Error failed to read data from socket: " + std::to_string(errno));
		return (NET_ERROR);
	}
	else
	{
		LogNetwork::logInfoMsg("Received deconnection notification from client");
        exitConnection(client->getSock());
        addNewClientDeco(client->getId());
	}
	return (SUCCESS);
}

ERR ServerNetwork::writeData(const std::string &data, __socket clientSocket)
{
    auto size = (__size)data.size();
	const char *dataToSend = data.c_str();

	if ((write(clientSocket, dataToSend, size)) == NET_ERROR)
	{
		LogNetwork::logFailureMsg("Error failed to write data to socket");
		return (NET_ERROR);
	}
	return (SUCCESS);
}

ERR ServerNetwork::sendData(const std::string &data, __client_id clientId)
{
    __clients_iterator it;

    if ((it = m_clients.find(clientId)) == m_clients.end())
        return (NET_ERROR);
    if (writeData(data, it->second->getSock()) == NET_ERROR)
        return (NET_ERROR);
    return (SUCCESS);
}

bool ServerNetwork::isSocketValid(__socket sock)
{
    __socket copyFd;
    
    errno = 0;
    copyFd = dup(sock);
    close(copyFd);
    return (!(errno == EBADF));
}

void ServerNetwork::exitAllClientConnection()
{
    __clients_iterator it = m_clients.begin();

    for (; it != m_clients.end(); it++)
        exitConnection(it->second->getSock());
}

ERR ServerNetwork::exitConnection(__socket sock)
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

void ServerNetwork::addNewClientDeco(__client_id clientId)
{
    m_clientsDecoToErase.push_back(clientId);
}

ERR ServerNetwork::eraseDecoClients() 
{
    for (int id : m_clientsDecoToErase)
    {
        if (eraseClientById(id) == NET_ERROR)
            return (NET_ERROR);
    }
    m_clientsDecoToErase.clear();
    return (SUCCESS);
}

ERR ServerNetwork::eraseClientById(__client_id clientId)
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