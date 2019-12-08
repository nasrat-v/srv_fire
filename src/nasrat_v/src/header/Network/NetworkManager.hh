//
// Created by nasrat_v on 3/3/19.
//

#ifndef __NETWORK_MANAGER_HH__
#define __NETWORK_MANAGER_HH__

# define PORT   5050

#include "AsyncServer.hh"

class NetworkManager
{
public:
    NetworkManager();
    ~NetworkManager();

    ERR                 startAsyncNetwork();
    void                stopAsyncNetwork();
    bool                isNewClientConnected();
    __client_id_vector  getNewClientConnected();
    bool                isNewDataReceived(__client_id clientId);
    __data_vector       getNewDataReceived(__client_id clientId);

private:
    AsyncServer         m_server;
    std::promise<void>  m_serverExitSignal;
    __client_id_vector  m_newClients;

    ERR                                 initServer();
    const AsyncServer::__t_server_param initConfigurationServer();
    void                                resetString(std::string &str);
    void                                formatData(std::string &data);
};

#endif /* !__NETWORK_MANAGER_HH__ */
