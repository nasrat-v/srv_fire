
#ifndef __CLIENT_HH__
#define __CLIENT_HH__

#include <stack>

#include "NetworkTypes.hh"

class Client
{
public:
    Client();
    ~Client();

private:
    __client_id                 _id;
    __socket                    _sock;
    __sockaddr_in               _sin;
    uint32_t                    _sin_size;
    std::stack<__client_data>   _stackData;
};

#endif /* !__CLIENT_HH__ */