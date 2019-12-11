
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
		header.read_size = 0;
		header.pk_size = convertBytesBufferToInt(buff);
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

int PacketsManager::convertBytesBufferToInt(const char *bytesBuff)
{
	int intArray[HEADER_BUFF_SIZE] = { 0 };

	if ((intArray[0] = (bytesBuff[0] << 24)) < 0)
		intArray[0] += (UINT8_MAX + 1);
	if ((intArray[1] = (bytesBuff[1] << 16)) < 0)
		intArray[1] += (UINT8_MAX + 1);
	if ((intArray[2] = (bytesBuff[2] << 8)) < 0)
		intArray[2] += (UINT8_MAX + 1);
	if ((intArray[3] = (bytesBuff[3] << 0)) < 0)
		intArray[3] += (UINT8_MAX + 1);
	return (intArray[0] | intArray[1] | intArray[2] | intArray[3]);
}