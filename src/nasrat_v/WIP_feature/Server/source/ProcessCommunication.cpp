//
// Created by nasrat_v on 3/3/19.
//

#include "../header/ProcessCommunication.hh"

ProcessCommunication::ProcessCommunication() = default;

ProcessCommunication::~ProcessCommunication() = default;

ERR ProcessCommunication::initServer()
{
    ServerNetwork::__t_server_param srvParam;

    srvParam = initConfigurationServer();
    if (m_network.initServer(srvParam) == NET_ERROR)
        return (NET_ERROR);
    return (SUCCESS);
}

const ServerNetwork::__t_server_param ProcessCommunication::initConfigurationServer()
{
    ServerNetwork::__t_server_param srvParam;

    memset(&srvParam, 0, sizeof(srvParam));
    srvParam.srv_ip_type = AF_INET;
    srvParam.srv_socket_type = SOCK_STREAM;
    srvParam.srv_protocol = IPPROTO_TCP;
    srvParam.srv_ip_addr_cl = INADDR_ANY;
    srvParam.srv_port = PORT;
    return (srvParam);
}

ERR ProcessCommunication::communicateWithServer()
{
    std::ofstream file;
    static int count = 0;
    __data_vector data;

    if (initServer() == NET_ERROR)
        return (NET_ERROR);
    m_network.startServer();
    while (42)
    {
        if (m_network.isNewDataReceived(0))
        {
            data = m_network.getLastDataReceived(0);
            for (__packet_data packet : data)
            {
                file.open(PATH_RCV_FILE + std::to_string(count) + FORMAT_RCV_FILE);
                file << packet;
                file.close();
                count++;
            }
        }
        usleep(1);
    }
    m_network.stopServer();
    return (SUCCESS);
}