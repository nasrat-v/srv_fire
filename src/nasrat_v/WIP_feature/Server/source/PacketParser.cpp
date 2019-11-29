
#include "../header/PacketParser.hh"

PacketParser::PacketParser() = default;

PacketParser::~PacketParser() = default;

void PacketParser::findTypePacket(__t_client_packet &packet)
{
    size_t pos;
    __t_packet_header_pos pckPos;

    if (isFullPacket(packet.pk_data, pckPos))
        packet.pk_type = e_type_packet::FULL;
    else if (isStartPacket(packet.pk_data, pckPos))
        packet.pk_type = e_type_packet::START;
    else if (isEndPacket(packet.pk_data, pckPos))
        packet.pk_type = e_type_packet::END;
    else if (!containStartHeader(packet.pk_data) && !containEndHeader(packet.pk_data))
        packet.pk_type = e_type_packet::MIDDLE;
    else if (isEndPlusSartPacket(packet.pk_data, pckPos))
    {

    }
    // parser le packet et definir son type
    // si le packet est une fin
    // mais qu'il contient le debut d'un autre packet
    // le split
    // concatener la fin avec le debut et milieu de la stack qui correspond
    // push le debut dans la bonne stack
    packet.pk_type = e_type_packet::FULL;
}

size_t PacketParser::containStartHeader(const std::string &data)
{
    return (data.find(HEADER_START_PCK));
}

size_t PacketParser::containEndHeader(const std::string &data)
{
    return (data.find(HEADER_END_PCK));
}

bool PacketParser::containFullPacket(const std::string &data, __t_packet_header_pos &pckPos)
{
    return (((pckPos.start_pos = containStartHeader(data)) != std::string::npos) &&
            ((pckPos.end_pos = containEndHeader(data)) != std::string::npos) && 
            (pckPos.start_pos < pckPos.end_pos));
}

bool PacketParser::isStartPacket(const std::string &data, __t_packet_header_pos &pckPos)
{
    return (((pckPos.start_pos = containStartHeader(data)) != std::string::npos) &&
            (containEndHeader(data) == std::string::npos) &&
            (pckPos.start_pos == 0));
}

bool PacketParser::isEndPacket(const std::string &data, __t_packet_header_pos &pckPos)
{
    return (((pckPos.end_pos = containEndHeader(data)) != std::string::npos) &&
            (containStartHeader(data) == std::string::npos) &&
            (pckPos.end_pos == ((data.size() - 1) - std::string(HEADER_END_PCK).size()))) /////////// a tester
}

bool PacketParser::isFullPacket(const std::string &data, __t_packet_header_pos &pckPos)
{
    return ((containFullPacket(data, pckPos)) && 
            (pckPos.start_pos == 0) &&
            (pckPos.end_pos == ((data.size() - 1) - std::string(HEADER_END_PCK).size()))); /////////// a tester
}

bool PacketParser::isEndPlusSartPacket(const std::string &data, __t_packet_header_pos &pckPos)
{
    return (((pckPos.start_pos = containStartHeader(data)) != std::string::npos) &&
            ((pckPos.end_pos = containEndHeader(data)) != std::string::npos) && 
            (pckPos.start_pos > pckPos.end_pos));
}