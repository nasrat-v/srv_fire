//
// Created by nasrat_v on 3/3/19.
//

#ifndef __NETWORK_MANAGER_HH__
#define __NETWORK_MANAGER_HH__

# define PORT               5050
# define PATH_RCV_FILE      "../files_received/file"
# define FORMAT_RCV_FILE    ".png"

#include "AsyncServer.hh"

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();

    ERR                             startNetwork();
    void                            stopNetwork();
    bool                            isNewClientConnected();
    const std::vector<__client_id>  &getNewClientConnected();
    bool                            isNewDataReceived(__client_id clientId);
    const __data_vector             &getNewDataReceived(__client_id clientId);

private:
    /* Attributes */
    AsyncServer                 m_server;
    std::promise<void>          m_serverExitSignal;
    std::vector<__client_id>    m_newClients;

    /* Methods */
    ERR                                 initServer();
    const AsyncServer::__t_server_param initConfigurationServer();
    void                                resetString(std::string &str);
    void                                formatData(std::string &data);
};

#endif /* !__NETWORK_MANAGER_HH__ */
