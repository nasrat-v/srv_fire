
#include "../header/ProcessCommunication.hh"

int main()
{
    ProcessCommunication com;
    
    if (com.communicateWithServer() == NET_ERROR)
        return (1);
    return (0);
}


ERR NetworkManager::communicateWithServer()
{
    std::ofstream file;
    static int count = 0;
    __data_vector data;
    std::vector<__client_id> newClients;

    if (initServer() == NET_ERROR)
        return (NET_ERROR);
    m_server.startServer();
    while (42)
    {
        if (m_server.isNewDataReceived(0))
        {
            data = m_server.getNewDataReceived(0);
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
    m_server.stopServer();
    return (SUCCESS);
}