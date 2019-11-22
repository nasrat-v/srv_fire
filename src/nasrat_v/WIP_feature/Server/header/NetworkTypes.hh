
#ifndef __NETWORK_TYPES_HH__
#define __NETWORK_TYPES_HH__

#ifdef _WIN32
#elif __linux__ || __unix__ || __unix || unix || __APPLE__ || __MACH__
    #include <unistd.h>
    #include <netdb.h>
    #include <iostream>
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
#endif
    typedef struct timeval      __timeval;
    typedef uint_fast16_t       __client_id;
    typedef std::string         __client_data;

#endif /* !__NETWORK_TYPES_HH__ */