
#ifndef __PACKETS_MANAGER_HH__
#define __PACKETS_MANAGER_HH__

# define HEADER_BUFF_SIZE   4
# define MAX_ALLOC_PACKET   3000000 // bytes
# define DECO_NOTIF         (ERR)0x2A
# define TRUNCATED_PACKET   (ERR)0x2B
# define IGNORE_PACKET      (ERR)0x2C
# define RESPONSE_SUCCESS   "OK\n"

#include <stack>
#include <map>
#include <memory>
#include <cstring>
#include <ctime>

#include "Packet.hh"
#include "Log/LogNetwork.hh"

typedef std::shared_ptr<__t_packet>         __packet_ptr;
typedef std::map<__client_id, __packet_ptr> __client_pckptr_map;

class PacketsManager
{
public:
    PacketsManager();
    ~PacketsManager();

    ERR         receivePacket(__socket sock, __t_packet &packet);
    ERR		    sendResponse(const std::string &data, __socket clientSocket);
    bool        isPacketTruncated(__client_id clientId) const;

private:
    __client_pckptr_map m_truncPackets;

    ERR         readHeader(__socket sock, __t_packet_header &header);
    ERR         readPacket(__socket sock, __t_packet &packet);
    int         convertBytesBufferToInt(char *bytesBuff);
    __t_packet  getTruncPacket(__client_id clientId) const;
    void        addTruncPacket(const __t_packet &packet);
    void        removeTruncPacket(__client_id clientId);
    void        removeClientAndTruncPacket(__client_id clientId);
};

#endif /* !__PACKETS_MANAGER_HH__ */