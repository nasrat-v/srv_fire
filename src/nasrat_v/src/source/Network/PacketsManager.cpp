
#include "../../header/Network/PacketsManager.hh"

PacketsManager::PacketsManager() = default;

PacketsManager::~PacketsManager() = default;

ERR PacketsManager::receivePacket(__socket sock, __t_packet &packet)
{
	ERR status;

    if ((status = readHeader(sock, packet.pk_header)) != SUCCESS)
		return (status);
    if (packet.pk_header.pk_size > 0)
    {
        if ((status = readPacket(sock, packet)) != SUCCESS)
            return (status);
    }
	return (SUCCESS);
}

ERR PacketsManager::readHeader(__socket sock, __t_packet_header &header)
{
    __ret ret;
	char buff[(HEADER_BUFF_SIZE + sizeof(char))] = { 0 };

    errno = 0;
	if ((ret = read(sock, buff, HEADER_BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		header.read_size = 0;
		header.pk_size = atoi(buff);
		LogNetwork::logInfoMsg("Packet received");
		LogNetwork::logSomething("Header size: " + std::to_string(header.pk_size));
	}
	else if (ret < 0)
	{
		LogNetwork::logFailureMsg("Error failed to read data from socket: " + std::to_string(errno));
		return (NET_ERROR);
	}
	else
	{
		LogNetwork::logInfoMsg("Received deconnection notification from client");
		return (NET_DECO);
	}
	return (SUCCESS);
}

ERR PacketsManager::readPacket(__socket sock, __t_packet &packet)
{
	__ret ret;
	ssize_t sizeToRead = (packet.pk_header.pk_size - packet.pk_header.read_size);
	char *buff = new char[(sizeToRead + sizeof(char))]();

    errno = 0;
	if ((ret = read(sock, buff, sizeToRead)) > 0)
	{
		packet.pk_data.append(buff, ret);
		packet.pk_header.read_size += ret;
		LogNetwork::logSomething("Read size: " + std::to_string(packet.pk_header.read_size));
	}
	else if (ret < 0)
	{
		LogNetwork::logFailureMsg("Error failed to read data from socket: " + std::to_string(errno));
		delete (buff);
		return (NET_ERROR);
	}
	else
	{
		LogNetwork::logInfoMsg("Received deconnection notification from client");
		delete (buff);
		return (NET_DECO);
	}
	if (ret < sizeToRead)
		return (readPacket(sock, packet));
	delete (buff);
	return (SUCCESS);
}