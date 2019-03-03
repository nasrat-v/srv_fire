//
// Created by nasrat_v on 3/3/19.
//

#ifndef OPENCV_SRV_PROCESSCOMMUNICATION_HH
#define OPENCV_SRV_PROCESSCOMMUNICATION_HH

# define IPADDR     "127.0.0.1"
# define PORT       4343
# define TYPE_ASK   "type"
# define TYPE_RESP  "IA"
# define ID_ASK     "ID"

#include "ClientNetwork.hh"

class ProcessCommunication
{
public:
    ProcessCommunication();
    ~ProcessCommunication();

    ERR                                 initHttpsClient();
    ERR                                 communicateWithServer(const std::string &msg);

private:
    /* Attributes */
    ClientNetwork                       _network;

    /* Methods */
    const ClientNetwork::t_serverParam  initConfigurationServer();
};

#endif //OPENCV_SRV_PROCESSCOMMUNICATION_HH
