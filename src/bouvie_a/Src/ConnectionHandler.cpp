//
//  ConnectionHandler.cpp
//  srv-fire
//
//  Created by Alexandre Bouvier on 12/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#include "../Include/ConnectionHandler.h"

ConnectionHandler::ConnectionHandler() {
    _fdConnect = socket(AF_INET, SOCK_STREAM, 0);
    _srvInf.sin_family = AF_INET;
    _srvInf.sin_addr.s_addr = INADDR_ANY;
    _srvInf.sin_port = htons(PORT);
    bind(_fdConnect, (struct sockaddr*)&_srvInf, sizeof(_srvInf));
    listen(_fdConnect, MAX_CLI);
}

ConnectionHandler::~ConnectionHandler(){
}

int     ConnectionHandler::AddCli(int newSock){
    _cli[newSock] = new BusinessLogicManager(newSock);
    return (0);
}

void    ConnectionHandler::start()
{
    int newSock;
    struct sockaddr_in  cliInf;
    int size = sizeof(cliInf);
    
    while ((newSock = accept(_fdConnect, (struct sockaddr *)&cliInf, (socklen_t*)&size))){
        std::cout << "New cli " << newSock << std::endl;
        AddCli(newSock);
    }
 }
