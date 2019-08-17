//
//  connectionHandler.h
//  srv-fire
//
//  Created by Alexandre Bouvier on 12/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#ifndef ConnectionHandler_h
#define ConnectionHandler_h

#include "BusinessLogicManager.hh"
#include "CommandAnalyzer.hh"
#include "../../Utilitary/loger.hpp"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <functional>
#include <fstream>
#include <netdb.h>
#include <netinet/in.h>
#include <map>
#include <thread>
#include <vector>

extern loger Log;

class connectionHandler {
private:
    std::thread                             _udpThread;
    PacketHandler                           _network;
    CommandAnalyzer                         commandManager;
    int                                     _port = -1;
    int                                     _maxCli = 10;
    fd_set                                  _rfds;

    std::map<std::string, BusinessLogicManager*>    _cli;
    std::map<std::string, std::thread>              _thread;

    std::vector<std::thread>    _connectionThread;

    struct sockaddr_in                      _tcpSrvInf;
    int                                     _tcpConnect;

    socklen_t len;
    struct sockaddr_in                      _udpSrvInf;
    struct sockaddr_in                      _udpCliInf;
    int                                     _udpConnect;

    std::string     getPacket(int);
    bool           sendPacket(int fd, std::string toSend);

    bool            addCli(char **env);
    bool            connectNewCli(char **env);

    void           setAllFd();
    void          readProperties();

    bool           identifyClient(int &newSock, std::string&, std::string&);

    void           udpHandler(char** env);
    int            recv_message(char *msg, size_t max_size);
public:
    bool           initConnection();
    bool           initUDPConnection();

    connectionHandler();
    ~connectionHandler();
    
    void    start(char **env);
};

#endif /* ConnectionHandler_h */
