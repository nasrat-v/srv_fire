
#ifndef __SERVERNETWORK_HH__
#define __SERVERNETWORK_HH__

#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <mutex>                                                                                         
#include <thread>
#include <future>
#include <algorithm>
#include <errno.h>

#include "PacketsManager.hh"

# define SIZE_BUFF		4096
# define MAX_CLIENT	    10
# define UWAIT_STOP     1

typedef std::shared_ptr<Client>                 __client_ptr;
typedef std::map<__client_id, __client_ptr>     __clients_map;
typedef __clients_map::iterator                 __clients_iterator;

class ServerNetwork
{
public:
    ServerNetwork();
    ~ServerNetwork();

    typedef struct		s_server_param
	{
        __in_addr_t     srv_ip_addr_cl; // ip address of client in network byte order - ex: INADDR_ANY
		uint16_t		srv_port; // port of server - ex: 5050
		int				srv_socket_type; // socket type used by server - ex: SOCK_STREAM
		int				srv_protocol; // ip protocol used by server - ex: IPPROTO_TCP for TCP protocol
        __sa_family_t   srv_ip_type; // ip type used by server - ex:: AF_INET for IPV4 or AF_INET6 for IPV6
	}					__t_server_param;

    ERR                 initServer(const __t_server_param &srvParam);
    void                startServer();
    void                stopServer();
	ERR		            sendData(const std::string &data, __client_id clientId);
    bool                isNewDataReceived(__client_id clientId);
    __data_vector       getLastDataReceived(__client_id clientId);

protected:
    __socket                    m_srvSock;
    __socket                    m_lastSockAdded;
    __sockaddr_in               m_srvSin;
    __t_server_param		    m_srvParam;
    __fd_set		            m_readf;
    __clients_map               m_clients;
    std::vector<__client_id>    m_clientsDecoToErase;
    std::mutex                  m_mutex;
    std::thread                 m_netThread;
    std::promise<void>          m_exitSignal;
    PacketsManager              m_packetsManager;


    ERR	                initSocket();
    ERR                 bindSocket();
    ERR                 listenSocket();
    ERR                 serverLoop(std::future<void> serverExitSignal);
    void                resetFdSet();
    ERR                 handleClient(__timeval *timeval);
    bool                isDataOnSocket(__socket sock);
    ERR                 receiveNewConnection();
    ERR                 acceptNewClient();
    void                addNewClient(__client_ptr client);
    ERR                 receiveDataFromClient();
    void                addNewDataReceived(__client_ptr client, const std::string &data);
    ERR		            readData(__client_ptr newClient);
    ERR		            writeData(const std::string &data, __socket clientSocket);
    bool                isSocketValid(__socket sock);
    void                exitAllClientConnection();
    ERR                 exitConnection(__socket sock);
    void                addNewClientDeco(__client_id clientId);
    ERR                 eraseDecoClients();
    ERR                 eraseClientById(__client_id clientId);
};

#endif /* !__SERVERNETWORK_HH__ */