
#ifndef __NETWORK_TYPES_HH__
#define __NETWORK_TYPES_HH__

# define NET_ERROR  (ERR)~0
# define NET_DECO   84

#include <unistd.h>
#include <netdb.h>
#include <iostream>

typedef ssize_t                 __ret;
typedef size_t                  __size;
typedef socklen_t               __err_size;
typedef in_addr_t               __binary_iptype;
typedef int                     __socket;
typedef struct sockaddr         __sockaddr;
typedef struct sockaddr_in      __sockaddr_in;
typedef sa_family_t             __sa_family_t;
typedef in_addr_t               __in_addr_t;
typedef fd_set                  __fd_set;
typedef uint32_t                __sockaddr_in_size;
typedef struct timeval          __timeval;
typedef uint_fast16_t           __client_id;
typedef std::string             __packet_data;

#endif /* !__NETWORK_TYPES_HH__ */