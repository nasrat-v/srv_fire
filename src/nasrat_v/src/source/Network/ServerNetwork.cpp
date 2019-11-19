
#include "../../header/Network/ServerNetwork.hh"

ServerNetwork::ServerNetwork() = default;

ServerNetwork::~ServerNetwork() = default;

ERR ServerNetwork::initSocket()
{
    if ((_sock = socket(_srvParam.ipType, _srvParam.socketType, _srvParam.protocol)) == NET_ERROR)
	{
		LogNetwork::logFailureMsg("Error socket initialization");
		return (NET_ERROR);
	}
	LogNetwork::logSuccessMsg("Successfully initialize socket: " + std::to_string(_sock));
	return (SUCCESS);
}

ERR ServerNetwork::initSockAddrStruct()
{
	memset(&_sin, 0, sizeof(_sin));
	_sin.sin_family = _srvParam.ipType;
	_sin.sin_port = htons(_srvParam.port);
    _sin.sin_addr.s_addr = _srvParam.ipAddrClient;
    if ((bind(_sock, (__sockaddr*)(&_sin), sizeof(__sockaddr))) == NET_ERROR)
    {
        LogNetwork::logFailureMsg("Error bind failed");
		return (NET_ERROR);
    }
    if ((listen(_sock, MAX_CLIENT)) == NET_ERROR)
    {
        LogNetwork::logFailureMsg("Error listen failed");
		return (NET_ERROR);
    }   
    _sockLast = _sock;
    return (SUCCESS);
}

ERR ServerNetwork::initNetworkServer(const t_serverParam &srvParam)
{
    _srvParam = srvParam;
    if (initSocket() == NET_ERROR)
		return (NET_ERROR);
    if (initSockAddrStruct() == NET_ERROR)
        return (NET_ERROR);
	return (SUCCESS);
}

void ServerNetwork::resetFdSet()
{
    FD_ZERO(&_readf);
    FD_SET(_sock, &_readf);
    for (t_client &client : _clients)
        FD_SET(client.sock, &_readf);
}

ERR ServerNetwork::handleClient(__timeval *timeval)
{
    resetFdSet();
    if (select((_sockLast + 1), &_readf, NULL, NULL, timeval) == NET_ERROR)
    {
        LogNetwork::logFailureMsg("Error select failed");
		return (NET_ERROR);
    }
    if (isDataOnSocket(_sock))
        receiveNewClient();
    if (receiveDataFromClient() == NET_ERROR) /* else if ? */ 
        return (NET_ERROR);
  return (SUCCESS);
}

bool ServerNetwork::isDataOnSocket(__socket sock)
{
    return (FD_ISSET(sock, &_readf));
}

ERR ServerNetwork::receiveNewClient()
{
    LogNetwork::logInfoMsg("New client connection");
    acceptNewClient();
    _sockLast = (_sockLast > getLastClient().sock) ? _sockLast : getLastClient().sock;
}

ERR ServerNetwork::acceptNewClient()
{
    t_client newClient;

    newClient.sinSize = sizeof(newClient.sin);
    if ((newClient.sock = accept(_sock, (__sockaddr*)(&newClient.sin), &newClient.sinSize)) == NET_ERROR)
	{
        LogNetwork::logFailureMsg("Error select failed");
		return (NET_ERROR);
    }
    _clients.push_back(newClient);
    return (SUCCESS);
}

ERR ServerNetwork::receiveDataFromClient()
{
    std::string data;
  
    for (t_client &client : _clients)
    {
        if (isDataOnSocket(client.sock))
        {
            if (readData(data) == NET_ERROR)
                return (NET_ERROR);
        }
    }
    return (SUCCESS);
}

const ServerNetwork::t_client &ServerNetwork::getLastClient() const
{
    return (_clients.back());
}

ERR	ServerNetwork::readData(std::string &data)
{
    __ret ret;
	char buff[(SIZE_BUFF + sizeof(char))] = { 0 };

	while ((ret = __read_socket(_sock, buff, SIZE_BUFF, 0)) == SIZE_BUFF)
	{
		data.append(buff, SIZE_BUFF);
		memset(buff, 0, (SIZE_BUFF + sizeof(char)));
	}
	if (ret > 0)
	{
		buff[ret] = '\0'; // to be sure
		data.append(buff, static_cast<unsigned long>(ret));
	}
	else if (ret < 0)
	{
		LogNetwork::logFailureMsg("Error failed to read data from socket");
		return (NET_ERROR);
	}
	else
	{
		LogNetwork::logInfoMsg("Received deconnection notification from client");
		return (SUCCESS);
	}
	LogNetwork::logSomething("\nReceived:\n" + data + "\n:From Server\n");
	return (SUCCESS);
}

ERR ServerNetwork::writeData(const std::string &data)
{
}

bool ServerNetwork::isDataToRead()
{
}

void ServerNetwork::clearSocket()
{
}