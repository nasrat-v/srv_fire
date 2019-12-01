
#ifndef __PACKETS_MANAGER_HH__
#define __PACKETS_MANAGER_HH__

#define HEADER_BUFF_SIZE    8

#include <stack>
#include <map>
#include <memory>

#include "Packet.hh"
#include "Log/LogNetwork.hh"

class PacketsManager
{
public:
    PacketsManager();
    ~PacketsManager();

    ERR     receivePacket(__socket sock, __t_packet &packet);

private:
    ERR     readHeader(__socket sock, __t_packet_header &header);
    ERR     readPacket(__socket sock, __t_packet &packet);
};

#endif /* !__PACKETS_MANAGER_HH__ */