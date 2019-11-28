
#include "../header/PacketsManager.hh"

PacketsManager::PacketsManager(__packets_stack_ptr freshPackets, 
                               __packets_map_ptr processedPackets) : m_freshPackets(std::move(freshPackets)), 
                                                                     m_processedPackets(std::move(processedPackets)) 
{
    m_tmpPacket = { 0, "" };
}

PacketsManager::~PacketsManager() = default;

void PacketsManager::processPackets()
{
    __t_client_packet packet = getTopPacket();

    findTypePacket(packet);
    switch (packet.pk_type)
    {
        case (e_type_packet::FULL):
            addPacketInProcessedMap(packet);
            break;
        case (e_type_packet::START):
        case (e_type_packet::MIDDLE):
            addPacketInHalfMap(packet);
            break;
        case (e_type_packet::END):
            addPacketInProcessedMap(concatHalfPackets(packet.cl_id));
            break;
    }
}

void PacketsManager::findTypePacket(__t_client_packet &packet)
{
    // parser le packet et definir son type
    // si le packet est une fin
    // mais qu'il contient le debut d'un autre packet
    // le split
    // concatener la fin avec le debut et milieu de la stack qui correspond
    // push le debut dans la bonne stack
    packet.pk_type = e_type_packet::FULL;
}

const __t_client_packet &PacketsManager::getTopPacket()
{
    m_tmpPacket = m_freshPackets->top();
    m_freshPackets->pop();
    return (m_tmpPacket);
}

void PacketsManager::addPacketInProcessedMap(const __t_client_packet &packet)
{
    __packets_map::iterator mapIt;
    __packets_stack         stackP;

    // si la stack exist deja
    if ((mapIt = m_processedPackets->find(packet.cl_id)) != m_processedPackets->end())
        mapIt->second.push(packet);
    else
    {
        stackP.push(packet); // sinon on la créer (first time)
        m_processedPackets->insert(std::make_pair(packet.cl_id, stackP));
    }
}

void PacketsManager::addPacketInHalfMap(const __t_client_packet &packet)
{
    __packets_map::iterator mapIt;
    __packets_stack         stackP;

    // si la clé existe deja on récupere la stack
    if ((mapIt = m_halfPackets.find(packet.cl_id)) != m_halfPackets.end())
        mapIt->second.push(packet);
    else
    {
        stackP.push(packet); // sinon on la créer (first time)
        m_halfPackets.insert(std::make_pair(packet.cl_id, stackP));
    }    
}

const __t_client_packet &PacketsManager::concatHalfPackets(__client_id clientId)
{
    // faire pop la stack
    // concate le debut le/les milieux et la fin en un seul packet
}