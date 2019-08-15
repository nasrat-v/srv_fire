//
// Created by nasrat_v on 3/3/19.
//

#ifndef OPENCV_SRV_PROCESSCOMMUNICATION_HH
#define OPENCV_SRV_PROCESSCOMMUNICATION_HH

# define IPADDR     "127.0.0.1"
# define PORT       4242
# define TYPE_ASK   "TYPE\n"
# define TYPE_RESP  "IA\n"
# define ID_ASK     "ID\n"

#include "ClientNetwork.hh"
#include "../../imageAnalyzing/src/header/ImageProvider.hh"

#include <mutex>
#include <thread>

class ProcessCommunication
{
public:
    ProcessCommunication();
    ~ProcessCommunication();

    ERR                                 initClient();
    void                                startThread(const std::string &idNetwork, ImageProvider *imageProvider);

private:
    /* Attributes */
    ClientNetwork                       _network;
    std::mutex                          _mutex;
    std::thread                         _netThread;

    /* Methods */
    const ClientNetwork::t_serverParam  initConfigurationServer();
    ERR                                 communicateWithServer(const std::string &idNetwork, ImageProvider *imageProvider);
    ERR                                 typeRequest();
    ERR                                 idRequest(const std::string &idNetwork);
    void                                resetString(std::string &str);
    void                                formatData(std::string &data);
};

#endif //OPENCV_SRV_PROCESSCOMMUNICATION_HH
