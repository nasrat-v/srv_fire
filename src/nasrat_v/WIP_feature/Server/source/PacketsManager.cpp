
#include "../header/PacketsManager.hh"

PacketsManager::PacketsManager(__packets_stk_ptr freshPackets, 
                               __packets_map_stk_ptr processedPackets) : m_freshPackets(std::move(freshPackets)), 
                                                                         m_processedPackets(std::move(processedPackets)) 
{
    m_tmpPacket = { 0, "" };
}

PacketsManager::~PacketsManager() = default;

void PacketsManager::readHeader(__socket sock)
{
    __ret ret;
	char buff[(HEADER_BUFF_SIZE + sizeof(char))] = { 0 };

    // faire un read de la taille du header dabord pour pouvoir lire la taille
    // puis faire read de la taille recu
    // pour eviter de réallouer faire un buffer circulaire (ou une string ?)
    errno = 0;
	if ((ret = read(sock, buff, HEADER_READ_SIZE)) > 0)
		
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