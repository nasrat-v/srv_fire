
#include "../header/ServerNetwork.hh"

ServerNetwork::ServerNetwork() : _emptyClient({ 0 })
{
    _tmpDataTopStack = { 0, "" };
}

ServerNetwork::~ServerNetwork()
{
    if (_netThread.joinable())
        _netThread.join();
}

void ServerNetwork::startServer()
{
    std::future<void> serverExitSignal = _exitSignal.get_future();
    
    _netThread = std::thread(&ServerNetwork::serverLoop, this, std::move(serverExitSignal));
    _netThread.detach();
}

void ServerNetwork::stopServer()
{
    LogNetwork::logInfoMsg("Server stop...");
    exitAllClientConnection();
    exitConnection(_sock);
    _exitSignal.set_value();
}

ERR ServerNetwork::initServer(const ServerNetwork::t_serverParam &srvParam)
{
    _srvParam = srvParam;
    if (initSocket() == NET_ERROR)
		return (NET_ERROR);
    if (bindSocket() == NET_ERROR)
        return (NET_ERROR);
    if (listenSocket() == NET_ERROR)
        return (NET_ERROR);
    _sockLast = _sock;
	return (SUCCESS);
}

ERR ServerNetwork::initSocket()
{
    int enable = 1;

    errno = 0;
    if ((_sock = socket(_srvParam._ip_type, _srvParam._socket_type, _srvParam._protocol)) == NET_ERROR)
	{
		LogNetwork::logFailureMsg("Error socket initialization: " + errno);
		return (NET_ERROR);
	}
    setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)); // allow kill
	LogNetwork::logSuccessMsg("Successfully initialize socket: " + std::to_string(_sock));
	return (SUCCESS);
}

ERR ServerNetwork::bindSocket()
{
    errno = 0;
	memset(&_sin, 0, sizeof(_sin));
	_sin.sin_family = _srvParam._ip_type;
	_sin.sin_port = htons(_srvParam._port);
    _sin.sin_addr.s_addr = _srvParam._ip_addr_client;
    if ((bind(_sock, (__sockaddr*)(&_sin), sizeof(__sockaddr))) == NET_ERROR)
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
    if ((listen(_sock, MAX_CLIENT)) == NET_ERROR)
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
            return (NET_ERROR);
    }
    return (SUCCESS);
}

void ServerNetwork::resetFdSet()
{
    FD_ZERO(&_readf);
    FD_SET(_sock, &_readf);
    for (const ServerNetwork::t_client &client : _clients)
        FD_SET(client._sock, &_readf);
}

ERR ServerNetwork::handleClient(__timeval *timeval)
{
    errno = 0;
    resetFdSet();
    if (select((_sockLast + 1), &_readf, NULL, NULL, timeval) == NET_ERROR)
    {
        LogNetwork::logFailureMsg("Error select failed: " + errno);
		return (NET_ERROR);
    }
    if (receiveNewConnection() == NET_ERROR)
        return (NET_ERROR);
    if (receiveDataFromClient() == NET_ERROR)
        return (NET_ERROR);
    return (SUCCESS);
}

ERR ServerNetwork::receiveNewConnection()
{
    if (isDataOnSocket(_sock))
    {
        LogNetwork::logInfoMsg("New client connection");
        if (acceptNewClient() == NET_ERROR)
            return (NET_ERROR);
        // update sockLast to the last socket accepted
        _sockLast = (_sockLast > getLastClient()._sock) ? _sockLast : getLastClient()._sock;
    }
    return (SUCCESS);
}

bool ServerNetwork::isDataOnSocket(__socket sock)
{
    return (FD_ISSET(sock, &_readf));
}

ERR ServerNetwork::acceptNewClient()
{
    ServerNetwork::t_client newClient;
    static __client_id id = 0;

    errno = 0;
    newClient._id = id++;
    newClient._sin_size = sizeof(newClient._sin);
    if ((newClient._sock = accept(_sock, (__sockaddr*)(&newClient._sin), &newClient._sin_size)) == NET_ERROR)
	{
        LogNetwork::logFailureMsg("Error accept failed: " + errno);
		return (NET_ERROR);
    }
    _clients.push_back(newClient);
    return (SUCCESS);
}

ERR ServerNetwork::receiveDataFromClient()
{
    std::string data;
  
    for (const ServerNetwork::t_client &client : _clients)
    {
        if (isDataOnSocket(client._sock))
        {
            if (readData(client) == NET_ERROR)
                return (NET_ERROR);
        }
    }
    return (SUCCESS);
}

const ServerNetwork::t_client &ServerNetwork::getLastClient() const
{
    return (_clients.back());
}

const ServerNetwork::t_client &ServerNetwork::getClient(__client_id clientId) const
{
    for (const ServerNetwork::t_client &client : _clients)
    {
        if (client._id == clientId)
            return (client);
    }
    return (_emptyClient);
}

ERR	ServerNetwork::readData(const ServerNetwork::t_client &client)
{
    __ret ret;
    std::string data;
	char buff[(SIZE_BUFF + sizeof(char))] = { 0 };

    errno = 0;
    LogNetwork::logSomething("Read Data");
	while ((ret = __read_socket(client._sock, buff, SIZE_BUFF, 0)) == SIZE_BUFF)
	{
		data.append(buff, SIZE_BUFF);
		memset(buff, 0, (SIZE_BUFF + sizeof(char)));
        LogNetwork::logSomething("Loop packet");
	}
	if (ret > 0)
	{
		buff[ret] = '\0'; // to be sure
		data.append(buff, static_cast<unsigned long>(ret));
        LogNetwork::logSomething("Loop last");
	}
	else if (ret < 0)
	{
		LogNetwork::logFailureMsg("Error failed to read data from socket: " + errno);
		return (NET_ERROR);
	}
	else
	{
		LogNetwork::logInfoMsg("Received deconnection notification from client");
        exitConnection(client._sock);
        eraseClientById(client._id);
		return (SUCCESS);
	}
    //LogNetwork::logSomething(data);
    addNewDataReceived(data, client._id);
	return (SUCCESS);
}

ERR ServerNetwork::writeData(const std::string &data, __socket clientSocket)
{
    auto size = (__size)data.size();
	const char *dataToSend = data.c_str();

	if ((__write_socket(clientSocket, dataToSend, size, 0)) == NET_ERROR)
	{
		LogNetwork::logFailureMsg("Error failed to write data to socket");
		return (NET_ERROR);
	}
	return (SUCCESS);
}

void ServerNetwork::addNewDataReceived(const std::string &data, __client_id clientId)
{
    _mutex.lock();
    _dataStack.push( { clientId , data } );
    _mutex.unlock();
}

bool ServerNetwork::isNewDataReceived()
{
    return (!_dataStack.empty());
}

const ServerNetwork::t_clientData &ServerNetwork::getLastDataReceived()
{
    _mutex.lock();
    _tmpDataTopStack = _dataStack.top();
    _dataStack.pop();
    _mutex.unlock();
    return (_tmpDataTopStack);
}

ERR ServerNetwork::sendData(const std::string &data, __client_id clientId)
{
    __socket clientSocket = getClient(clientId)._sock;
    
    if (writeData(data, clientSocket) == NET_ERROR)
        return (NET_ERROR);
    return (SUCCESS);
}

bool ServerNetwork::isSocketValid(__socket sock)
{
    __socket copy_fd;
    
    errno = 0;
    copy_fd = dup(sock);
    close(copy_fd);
    return (!(errno == EBADF));
}

void ServerNetwork::exitAllClientConnection()
{
    for (const ServerNetwork::t_client &client : _clients)
        exitConnection(client._sock);
}

void ServerNetwork::exitConnection(__socket sock)
{
    if (isSocketValid(sock))
    {
        shutdown(sock, SHUT_RDWR);
        close(sock);
    }
}

void ServerNetwork::eraseClientById(__client_id clientId)
{
    std::vector<ServerNetwork::t_client>::const_iterator it;

    if ((it = getIteratorClientById(clientId)) != _clients.end())
        _clients.erase(it);
}

const std::vector<ServerNetwork::t_client>::const_iterator ServerNetwork::getIteratorClientById(__client_id clientId)
{
    std::vector<ServerNetwork::t_client>::const_iterator it;

    for (it = _clients.begin(); it != _clients.end(); it++)
    {
        if (it->_id == clientId)
            return (it);
    }
    return (_clients.end());
}