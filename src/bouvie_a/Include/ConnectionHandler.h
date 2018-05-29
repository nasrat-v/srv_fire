//
//  ConnectionHandler.h
//  srv-fire
//
//  Created by Alexandre Bouvier on 12/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#ifndef ConnectionHandler_h
#define ConnectionHandler_h

#include "BusinessLogicManager.hh"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <map>
#include <thread>

# define PORT 1236
# define MAX_CLI 10

class ConnectionHandler {
private:
    std::map<int, BusinessLogicManager*>   _cli;
    struct sockaddr_in  _srvInf;
    int                 _fdConnect;
    
    int     AddCli(int newSock);
public:
    ConnectionHandler();
    ~ConnectionHandler();
    
    void    start();
};

#endif /* ConnectionHandler_h */
