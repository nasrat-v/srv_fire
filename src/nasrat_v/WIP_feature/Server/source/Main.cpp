
#include "../header/NetworkManager.hh"

int main()
{
    NetworkManager network;
    std::ofstream file;
    static int count = 0;
    __data_vector data;
    std::vector<__client_id> newClients;

    network.startNetwork();
    while (42)
    {
        if (network.isNewDataReceived(0))
        {
            data = network.getNewDataReceived(0);
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
    network.stopNetwork();
}