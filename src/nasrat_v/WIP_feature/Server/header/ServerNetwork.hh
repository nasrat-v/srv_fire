
#ifndef __SERVERNETWORK_HH__
#define __SERVERNETWORK_HH__

#ifdef _WIN32
	#include <winsock2.h>
	#include <Ws2tcpip.h>
	#include <io.h>
#elif __linux__ || __unix__ || __unix || unix || __APPLE__ || __MACH__
    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <stdio.h>
	#include <cstring>
#endif

#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <mutex>                                                                                         
#include <thread>
#include <future>
#include <errno.h>

#include "Log/LogNetwork.hh"

# define NET_ERROR		(ERR)~0
# define SIZE_BUFF		4096
# define MAX_CLIENT	    1
# define UWAIT_STOP     1

#ifdef _WIN32s
    # define __read_socket(a, b, c, d)  recv(a, b, c, d)
    # define __write_socket(a, b, c, d) send(a, b, c, d)
    # define __close_socket             closesocket
#elif __linux__ || __unix__ || __unix || unix || __APPLE__ || __MACH__
    # define __read_socket(a, b, c, d)  read(a, b, c)
    # define __write_socket(a, b, c, d) write(a, b, c)
    # define __close_socket             close
#endif

#ifdef _WIN32
    typedef int                 __ret;
    typedef int                 __size;
    typedef int                 __err_size
    typdef  ULONG               __binary_iptype;
    typedef SOCKET              __socket;
    typedef struct SOCKADDR     __sockaddr;
	typedef struct SOCKADDR_IN  __sockaddr_in;
#elif __linux__ || __unix__ || __unix || unix || __APPLE__ || __MACH__
    typedef ssize_t             __ret;
    typedef size_t              __size;
    typedef socklen_t           __err_size;
    typedef in_addr_t           __binary_iptype;
	typedef int                 __socket;
    typedef struct sockaddr     __sockaddr;
	typedef struct sockaddr_in  __sockaddr_in;
    typedef struct timeval      __timeval;
    typedef uint_fast16_t       __client_id;
#endif
    

class ServerNetwork
{
public:
    ServerNetwork();
    ~ServerNetwork();

    typedef struct		s_serverParam
	{
        in_addr_t       ipAddrClient; // ip address of client in network byte order - ex: INADDR_ANY
		uint16_t		port; // port of server - ex: 6667 - can't be NULL
		int				socketType; // socket type used by server - ex: SOCK_STREAM - can't be NULL
		int				protocol; // ip protocol used by server - ex: IPPROTO_TCP for TCP protocol - can't be NULL
#ifdef _WIN32
        int				ipType; // ip type used by server - ex:: AF_INET for IPV4 or AF_INET6 for IPV6 - can't be NULL
#elif __linux__ || __unix__ || __unix || unix || __APPLE__ || __MACH__
        sa_family_t     ipType; // ip type used by server - ex:: AF_INET for IPV4 or AF_INET6 for IPV6 - can't be NULL
#endif
	}					t_serverParam;

    typedef struct      s_clientData
    {
        __client_id     clientId;
        std::string     data;
    }                   t_clientData;

    typedef struct      s_client
    {
        __client_id     id;
        __socket        sock;
        __sockaddr_in   sin;
        uint32_t        sinSize;
    }                   t_client;

    ERR                 initServer(const t_serverParam &srvParam);
    void                startServer();
    void                stopServer();
    bool	            isNewDataReceived();
    const t_clientData  &getLastDataReceived();
	ERR		            sendData(const std::string &data, __client_id clientId);

protected:
    __socket                    _sock;
    __socket                    _sockLast;
    __sockaddr_in               _sin;
    t_serverParam		        _srvParam;
    fd_set		                _readf;
    std::vector<t_client>       _clients;
    std::stack<t_clientData>    _dataStack;
    t_clientData                _tmpDataTopStack;
    std::mutex                  _mutex;                                                           
    std::thread                 _netThread;
    std::promise<void>          _exitSignal;
    const t_client              _emptyClient;

    ERR	                initSocket();
    ERR                 bindSocket();
    ERR                 listenSocket();
    ERR                 serverLoop(std::future<void> serverExitSignal);
    void                resetFdSet();
    ERR                 handleClient(__timeval *timeval);
    ERR                 receiveNewConnection();
    ERR                 acceptNewClient();
    ERR                 receiveDataFromClient();
    bool                isDataOnSocket(__socket sock);
    ERR		            readData(const ServerNetwork::t_client &client);
    ERR		            writeData(const std::string &data, __socket clientSocket);
    void                addNewDataReceived(const std::string &data, __client_id clientId);
    const t_client      &getLastClient() const;
    const t_client      &getClient(__client_id clientId) const;
    bool                isSocketValid(__socket sock);
    void                exitAllClientConnection();
    void                exitConnection(__socket sock);
};

#endif /* !__SERVERNETWORK_HH__ */