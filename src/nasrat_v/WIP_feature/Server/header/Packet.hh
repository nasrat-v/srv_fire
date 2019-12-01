
#ifndef __PACKET_HH__
#define __PACKET_HH_

#include "Client.hh"

enum e_type_packet
{
    UNKNOWN,
    START,
    END,  
    MIDDLE,
    FULL
};

typedef struct          s_packet_header
{
    size_t              pk_size;
    size_t              read_size;
}                       __t_packet_header;

typedef struct          s_packet
{
    __client_id         cl_id;
    __packet_data       pk_data;
    e_type_packet       pk_type;
    __t_packet_header   pk_header;
}                       __t_packet;

#endif /* !__PACKET_HH__ */