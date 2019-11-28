//
// Created by nasrat_v on 3/3/19.
//

#ifndef __PROCESSCOMMUNICATION_HH__
#define __PROCESSCOMMUNICATION_HH__

# define PORT               5050
# define PATH_RCV_FILE      "files_received/file"
# define FORMAT_RCV_FILE    ".png"

#include "ServerNetwork.hh"

class ProcessCommunication
{
public:
    ProcessCommunication();
    ~ProcessCommunication();

    ERR                                     communicateWithServer();

private:
    /* Attributes */
    ServerNetwork                           m_network;
    std::promise<void>                      m_serverExitSignal;

    /* Methods */
    ERR                                     initServer();
    const ServerNetwork::__t_server_param   initConfigurationServer();
    void                                    resetString(std::string &str);
    void                                    formatData(std::string &data);
};

#endif /* !__PROCESSCOMMUNICATION_HH__ */
