
#ifndef __PACKET_PARSER_HH__
#define __PACKET_PARSER_HH__

# define HEADER_START_PCK   "[Md2Pnv0Tx}"
# define HEADER_END_PCK     "{xT0vnP2dM]"

#include "Packet.hh"

class PacketParser
{
public:
    PacketParser();
    ~PacketParser();

    void    findTypePacket(__t_client_packet &packet);

private:
    size_t  containStartHeader(const std::string &data);
    size_t  containEndHeader(const std::string &data);
    bool    containFullPacket(const std::string &data, __t_packet_header_pos &pckPos);
    bool    isStartPacket(const std::string &data, __t_packet_header_pos &pckPos);
    bool    isEndPacket(const std::string &data, __t_packet_header_pos &pckPos);
    bool    isFullPacket(const std::string &data, __t_packet_header_pos &pckPos);
    bool    isEndPlusSartPacket(const std::string &data, __t_packet_header_pos &pckPos);
};

#endif /* !__PACKET_PARSER_HH__ */