
#ifndef __PACKETS_MANAGER_HH__
#define __PACKETS_MANAGER_HH__

#define HEADER_BUFF_SIZE    4
#define TIMEOUT_TRUNCATED   1
#define MAX_ALLOC_PACKET    3000000
#define IGNORE_PACKET       (ERR)-1
#define RESPONSE_SUCCESS    "OK\n"

#include <stack>
#include <map>
#include <memory>
#include <cstring>
#include <ctime>

#include "Packet.hh"
#include "Log/LogNetwork.hh"

class PacketsManager
{
public:
    PacketsManager();
    ~PacketsManager();

    ERR     receivePacket(__socket sock, __t_packet &packet);
    ERR		sendResponse(const std::string &data, __socket clientSocket);

private:
    ERR     readHeader(__socket sock, __t_packet_header &header);
    ERR     readPacket(__socket sock, __t_packet &packet);
    int     convertBytesBufferToInt(char *bytesBuff);
};

#endif /* !__PACKETS_MANAGER_HH__ */