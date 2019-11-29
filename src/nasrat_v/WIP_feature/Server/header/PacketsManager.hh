
#ifndef __PACKETS_MANAGER_HH__
#define __PACKETS_MANAGER_HH__

#define HEADER_BUFF_SIZE    8
#define HEADER_READ_SIZE    1

#include <stack>
#include <map>
#include <memory>

#include "PacketParser.hh"
#include "Log/LogNetwork.hh"

typedef std::vector<__t_client_packet>          __packets_vec;
typedef std::stack<__t_client_packet>           __packets_stk;
typedef std::map<__client_id, __packets_vec>    __packets_map_vec;
typedef std::map<__client_id, __packets_stk>    __packets_map_stk;
typedef std::shared_ptr<__packets_stk>          __packets_stk_ptr;
typedef std::shared_ptr<__packets_map_stk>      __packets_map_stk_ptr;

class PacketsManager
{
public:
    PacketsManager(__packets_stk_ptr freshPackets, 
                   __packets_map_stk_ptr processedPackets);
    ~PacketsManager();

    void                    readHeader(__socket sock);

private:
    __packets_stk_ptr       m_freshPackets;
    __packets_map_stk_ptr   m_processedPackets;
    __packets_map_vec       m_fragmentedPackets;
    __t_client_packet       m_tmpPacket;   
    PacketParser            m_pckParser;
};

#endif /* !__PACKETS_MANAGER_HH__ */