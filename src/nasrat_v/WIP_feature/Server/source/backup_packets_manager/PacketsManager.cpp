
#include "../header/PacketsManager.hh"

PacketsManager::PacketsManager(__packets_stk_ptr freshPackets, 
                               __packets_map_stk_ptr processedPackets) : m_freshPackets(std::move(freshPackets)), 
                                                                         m_processedPackets(std::move(processedPackets)) 
{
    m_tmpPacket = { 0, "" };
}

PacketsManager::~PacketsManager() = default;

ERR PacketsManager::processPackets()
{
    ERR status = SUCCESS;
    __t_client_packet fullPck;
    __t_client_packet packet = getTopPacket();

    m_pckParser.findTypePacket(packet);
    switch (packet.pk_type)
    {
        case (e_type_packet::FULL):
            addPacketInProcessedMap(packet);
            break;
        case (e_type_packet::START):// faire check il ne doit rien y avoir avant de mettre un start
            status = addStartPacketInHalfVector(packet);
        case (e_type_packet::MIDDLE): // faire check il doit y avoir un start avant de mettre un middle
            status = addMiddlePacketInHalfVector(packet);
            break;
        case (e_type_packet::END):
            status = concatFragmentedPackets(packet, fullPck);
            addPacketInProcessedMap(fullPck);
            break;
    }
    return (status);
}

const __t_client_packet &PacketsManager::getTopPacket()
{
    m_tmpPacket = m_freshPackets->top();
    m_freshPackets->pop();
    return (m_tmpPacket);
}

void PacketsManager::addPacketInProcessedMap(const __t_client_packet &packet)
{
    __packets_stk stackP;
    __packets_map_stk::iterator mapIt;

    // si la stack exist deja
    if ((mapIt = m_processedPackets->find(packet.cl_id)) != m_processedPackets->end())
        mapIt->second.push(packet);
    else
    {
        stackP.push(packet); // sinon on la créer (first time)
        m_processedPackets->insert(std::make_pair(packet.cl_id, stackP));
    }
}

ERR PacketsManager::addStartPacketInHalfVector(const __t_client_packet &packet)
{
    __packets_vec vecP;
    __packets_map_vec::iterator mapIt;

    // si la clé existe deja on récupere le vector
    if ((mapIt = m_fragmentedPackets.find(packet.cl_id)) != m_fragmentedPackets.end())
    {
        if (mapIt->second.empty())
            mapIt->second.push_back(packet);
        else
        {
            LogNetwork::logFailureMsg("Error vector was not empty when pushing Start Packet");
            return (NET_ERROR);
        }
    }
    else
    {
        vecP.push_back(packet); // sinon on le créer (first time)
        m_fragmentedPackets.insert(std::make_pair(packet.cl_id, vecP));
    }
    return (SUCCESS);
}

ERR PacketsManager::addMiddlePacketInHalfVector(const __t_client_packet &packet)
{
    __packets_map_vec::iterator mapIt;

    // si la clé existe deja on récupere le vector
    if ((mapIt = m_fragmentedPackets.find(packet.cl_id)) != m_fragmentedPackets.end())
    {
        if (mapIt->second.begin()->pk_type == e_type_packet::START) // si le premier élement est bien un start
            mapIt->second.push_back(packet);
        else
        {
            LogNetwork::logFailureMsg("Error vector first element was not Start when pushing Middle Packet");
            return (NET_ERROR);
        }
    }
    else
    {
        LogNetwork::logFailureMsg("Error vector was not created when pushing Middle Packet");
        return (NET_ERROR);
    }
    return (SUCCESS);
}

ERR PacketsManager::concatFragmentedPackets(const __t_client_packet &endPck, __t_client_packet &fullPck)
{
    __packets_map_vec::iterator mapIt;

    // si la clé existe deja on récupere le vector
    if ((mapIt = m_fragmentedPackets.find(endPck.cl_id)) != m_fragmentedPackets.end())
    {
        fullPck.cl_id = endPck.cl_id;
        fullPck.pk_type = e_type_packet::FULL;
        for (__t_client_packet pck : mapIt->second)
            fullPck.pk_data.append(pck.pk_data);
        fullPck.pk_data.append(endPck.pk_data); // on met le endPck a la fin du fullPck
    }
    else
    {
        LogNetwork::logFailureMsg("Error vector was not created when pushing End Packet");
        return (NET_ERROR);
    }
    return (SUCCESS);
}