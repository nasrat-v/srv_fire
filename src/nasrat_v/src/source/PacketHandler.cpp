//
//  Packet.cpp
//  srv-fire
//
//  Created by Alexandre Bouvier on 13/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#include "../header/PacketHandler.hh"

PacketHandler::PacketHandler(int Socket): _thread(&PacketHandler::readPacket, this)
{
    _embededSocket = Socket;
}

PacketHandler::~PacketHandler()
{
    close(_embededSocket);
    _thread.detach();
}

std::string  PacketHandler::getPacket()
{
    std::string     retour = "";

    if (_stack.size() > 0) {
        retour = _stack.at(0);
        _stack.erase(_stack.begin());
    }
    return (retour);
}

void    PacketHandler::sendPacket(std::string toSend)
{
    write(_embededSocket, std::string(toSend + "\n").c_str(), toSend.size() + 1);
}

void    PacketHandler::readPacket()
{
    char    buffer[4096];
    ssize_t     size;
    
    while ((size = read(_embededSocket, buffer, 4096)) > 0){
        buffer[size - 1] = 0;
        _stack.push_back(buffer);
    }
}
