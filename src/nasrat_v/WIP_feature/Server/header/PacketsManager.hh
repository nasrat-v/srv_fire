
#ifndef __PACKETS_MANAGER_HH__
#define __PACKETS_MANAGER_HH__

#include "Client.hh"
#include <stack>
#include <map>
#include <memory>

enum                e_type_packet
{
    UNKNOWN,
    START,
    END,
    MIDDLE,
    FULL
};

typedef struct      s_client_packet
{
    __client_id     cl_id;
    __packet_data   pk_data;
    e_type_packet   pk_type;
}                   __t_client_packet;

typedef std::stack<__t_client_packet>           __packets_stack;
typedef std::map<__client_id, __packets_stack>  __packets_map;
typedef std::shared_ptr<__packets_stack>        __packets_stack_ptr;
typedef std::shared_ptr<__packets_map>          __packets_map_ptr;

class PacketsManager
{
public:
    PacketsManager(__packets_stack_ptr freshPackets, 
                   __packets_map_ptr processedPackets);
    ~PacketsManager();

    void                    processPackets();

private:
    __packets_stack_ptr     m_freshPackets;
    __packets_map_ptr       m_processedPackets;
    __packets_map           m_halfPackets;
    __t_client_packet       m_tmpPacket;   

    void                    findTypePacket(__t_client_packet &packet);
    const __t_client_packet &getTopPacket();
    void                    addPacketInProcessedMap(const __t_client_packet &packet);
    void                    addPacketInHalfMap(const __t_client_packet &packet);
    const __t_client_packet &concatHalfPackets(__client_id clientId);
};

#endif /* !__PACKETS_MANAGER_HH__ */