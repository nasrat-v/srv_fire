//
// Created by nasrat_v on 3/3/19.
//

#ifndef __PROCESSCOMMUNICATION_HH__
#define __PROCESSCOMMUNICATION_HH__

# define PORT   4242

#include "ServerNetwork.hh"

class ProcessCommunication
{
public:
    ProcessCommunication();
    ~ProcessCommunication();

    ERR                                 communicateWithServer();

private:
    /* Attributes */
    ServerNetwork                       _network;
    std::promise<void>                  _serverExitSignal;

    /* Methods */
    ERR                                 initServer();
    const ServerNetwork::t_serverParam  initConfigurationServer();
    void                                resetString(std::string &str);
    void                                formatData(std::string &data);
};

#endif /* !__PROCESSCOMMUNICATION_HH__ */
