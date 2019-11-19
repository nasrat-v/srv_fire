
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
#include <vector>

#include "Log/LogNetwork.hh"

# define NET_ERROR		(ERR)~0
# define SIZE_BUFF		4096
# define MAX_CLIENT	    1

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
#endif

class ServerNetwork
{
public:
    ServerNetwork();
    ~ServerNetwork();

    typedef struct		s_serverParam
	{
        in_addr_t       ipAddrClient; // ip address of client in network byte order
		uint16_t		port; // port of server - ex: 6667 - can't be NULL
		int				socketType; // socket type used by server - ex: SOCK_STREAM - can't be NULL
		int				protocol; // ip protocol used by server - ex: IPPROTO_TCP for TCP protocol - can't be NULL
#ifdef _WIN32
        int				ipType; // ip type used by server - ex:: AF_INET for IPV4 or AF_INET6 for IPV6 - can't be NULL
#elif __linux__ || __unix__ || __unix || unix || __APPLE__ || __MACH__
        sa_family_t     ipType; // ip type used by server - ex:: AF_INET for IPV4 or AF_INET6 for IPV6 - can't be NULL
#endif
	}					t_serverParam;

    typedef struct      s_client
    {
        __socket        sock;
        __sockaddr_in   sin;
        uint32_t        sinSize;
    }                   t_client;

    ERR                 initNetworkServer(const t_serverParam &srvParam);
    ERR		            readData(std::string &data);
	ERR		            writeData(const std::string &data);
	bool	            isDataToRead();

protected:
    __socket                _sock;
    __socket                _sockLast;
    __sockaddr_in           _sin;
    t_serverParam		    _srvParam;
	bool				    _connected;
    fd_set		            _readf;
    std::vector<t_client>   _clients;

    ERR	                initSocket();
    ERR                 initSockAddrStruct();
    void                resetFdSet();
    ERR                 handleClient(__timeval *timeval);
    ERR                 receiveNewClient();
    ERR                 acceptNewClient();
    ERR                 receiveDataFromClient();
    bool                isDataOnSocket(__socket sock);
    const t_client      &getLastClient() const;
    void                clearSocket();
};

#endif /* !__SERVERNETWORK_HH__ */