
#ifndef __PACKET_HH__
#define __PACKET_HH_

#include "Client.hh"

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

typedef struct      s_packet_header_pos
{
    size_t          start_pos;
    size_t          end_pos;
}                   __t_packet_header_pos;

#endif /* !__PACKET_HH__ */