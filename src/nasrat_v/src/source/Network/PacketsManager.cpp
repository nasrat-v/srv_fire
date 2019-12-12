
#include "../../header/Network/PacketsManager.hh"

PacketsManager::PacketsManager() = default;

PacketsManager::~PacketsManager() = default;

ERR PacketsManager::receivePacket(__socket sock, __t_packet &packet)
{
	ERR status;

	if (!isPacketTruncated(packet.cl_id))
	{
    	if ((status = readHeader(sock, packet.pk_header)) == DECO_NOTIF)
			removeClientAndTruncPacket(packet.cl_id);
		if (status != SUCCESS)
			return (status);
    	if ((packet.pk_header.pk_size <= 0) || (packet.pk_header.pk_size >= MAX_ALLOC_PACKET))
		{
			LogNetwork::logFailureMsg("Error bad header size: " 
												+ std::to_string(packet.pk_header.pk_size));		
			return (IGNORE_PACKET);
		}
	}
	else
		packet = getTruncPacket(packet.cl_id);
	return (readPacket(sock, packet));
}

ERR PacketsManager::readHeader(__socket sock, __t_packet_header &header)
{
    __ret ret;
	char buff[(HEADER_BUFF_SIZE * sizeof(char))] = { 0 };

    errno = 0;
	if ((ret = read(sock, buff, HEADER_BUFF_SIZE)) > 0)
	{
		header.read_size = 0;
		header.pk_size = atoi(buff);//convertBytesBufferToInt(buff);
		#if (DEBUGNET_ACTIVE)
			LogNetwork::logInfoMsg("Packet received");
			for (int i = 0; i < ret; i++)
				printf("%d\n", buff[i]);
			LogNetwork::logSomething("Header size: " + std::to_string(header.pk_size));
		#endif
	}
	else if (ret < 0)
	{
		LogNetwork::logFailureMsg("Error failed to read data from socket: " + std::to_string(errno));
		return (NET_ERROR);
	}
	else
	{
		LogNetwork::logInfoMsg("Received deconnection notification from client");
		return (DECO_NOTIF);
	}
	return (SUCCESS);
}

ERR PacketsManager::readPacket(__socket sock, __t_packet &packet)
{
	__ret ret;
	ssize_t sizeToRead = (packet.pk_header.pk_size - packet.pk_header.read_size);
	char buff[(sizeToRead * sizeof(char))];

    errno = 0;
	memset(buff, 0, sizeToRead);
	if ((ret = read(sock, buff, sizeToRead)) > 0)
	{
		packet.pk_data.append(buff, ret);
		packet.pk_header.read_size += ret;
		#if (DEBUGNET_ACTIVE)
			LogNetwork::logSomething("Read size: " + std::to_string(packet.pk_header.read_size));
		#endif
	}
	else if (ret < 0)
	{
		LogNetwork::logFailureMsg("Error failed to read data from socket: " + std::to_string(errno));
		return (NET_ERROR);
	}
	else
	{
		removeClientAndTruncPacket(packet.cl_id);
		LogNetwork::logInfoMsg("Received deconnection notification from client");
		return (DECO_NOTIF);
	}
	if (ret < sizeToRead)
	{
		addTruncPacket(packet);
		return (TRUNCATED_PACKET);
	}
	removeTruncPacket(packet.cl_id);
	return (sendResponse(RESPONSE_SUCCESS, sock));
}

ERR PacketsManager::sendResponse(const std::string &data, __socket clientSocket)
{
    size_t size = data.size();
	const char *dataToSend = data.c_str();

	#if (DEBUGNET_ACTIVE)
		LogNetwork::logSomething("Send response: " + data);
	#endif
	if ((write(clientSocket, dataToSend, size)) == NET_ERROR)
	{
		LogNetwork::logFailureMsg("Error failed to write data to socket");
		return (NET_ERROR);
	}
	return (SUCCESS);
}

int PacketsManager::convertBytesBufferToInt(char *bytesBuff)
{
	int intArray[HEADER_BUFF_SIZE] = { 0 };

	if ((intArray[0] = ((bytesBuff[0] & 0xFF) << 24)) < 0)
		intArray[0] += (UINT8_MAX + 1);
	if ((intArray[1] = ((bytesBuff[1] & 0xFF) << 16)) < 0)
		intArray[1] += (UINT8_MAX + 1);
	if ((intArray[2] = ((bytesBuff[2] & 0xFF) << 8)) < 0)
		intArray[2] += (UINT8_MAX + 1);
	if ((intArray[3] = ((bytesBuff[3] & 0xFF) << 0)) < 0)
		intArray[3] += (UINT8_MAX + 1);
	return (intArray[0] | intArray[1] | intArray[2] | intArray[3]);
}

bool PacketsManager::isPacketTruncated(__client_id clientId) const
{
	__client_pckptr_map::const_iterator mapIt;

	if ((mapIt = m_truncPackets.find(clientId)) != m_truncPackets.end())
		return (mapIt->second != nullptr);
	return (false);
}

__t_packet PacketsManager::getTruncPacket(__client_id clientId) const
{
	return (*(m_truncPackets.at(clientId)));
}

void PacketsManager::addTruncPacket(const __t_packet &packet)
{
	__client_pckptr_map::iterator mapIt;

	if ((mapIt = m_truncPackets.find(packet.cl_id)) != m_truncPackets.end())
		mapIt->second = std::make_shared<__t_packet>(packet);
	else
		m_truncPackets.insert(std::make_pair(packet.cl_id, std::make_shared<__t_packet>(packet)));
}

void PacketsManager::removeTruncPacket(__client_id clientId)
{
	__client_pckptr_map::iterator mapIt;

	if ((mapIt = m_truncPackets.find(clientId)) != m_truncPackets.end())
		mapIt->second = nullptr;
}

void PacketsManager::removeClientAndTruncPacket(__client_id clientId)
{
	m_truncPackets.erase(clientId);
}