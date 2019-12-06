
#include "../header/PacketsManager.hh"

PacketsManager::PacketsManager() = default;

PacketsManager::~PacketsManager() = default;

ERR PacketsManager::receivePacket(__socket sock, __t_packet &packet)
{
	ERR status;

    if ((status = readHeader(sock, packet.pk_header)) != SUCCESS)
		return (status);
    if (packet.pk_header.pk_size > 0)
		return (readPacket(sock, packet));
	return (IGNORE_PACKET);
}

ERR PacketsManager::readHeader(__socket sock, __t_packet_header &header)
{
    __ret ret;
	char buff[(HEADER_BUFF_SIZE * sizeof(char))] = { 0 };

    errno = 0;
	if ((ret = read(sock, buff, HEADER_BUFF_SIZE)) > 0)
	{
		std::cout << "ret: " << ret << std::endl;
		unsigned int size = (((unsigned int)buff[0] << 24) | ((unsigned int)buff[1] << 16) | ((unsigned int)buff[2] << 8) | ((unsigned int)buff[3] << 0));
		unsigned int size_little = (((unsigned int)buff[3] << 24) | ((unsigned int)buff[2] << 16) | ((unsigned int)buff[1] << 8) | ((unsigned int)buff[0] << 0));
		std::cout << "size big: " << size << std::endl;
		std::cout << "size little: " << size_little << std::endl;
		for (int i = 0; i < ret; i++)
			printf("%d\n", (unsigned int)buff[i]);
		header.read_size = 0;
		header.pk_size = size;
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
	char *buff = new char[(sizeToRead * sizeof(char))]();

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