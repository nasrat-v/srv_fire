//
//  Packet.hpp
//  srv-fire
//
//  Created by Alexandre Bouvier on 13/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#ifndef PacketHandler_h
#define PacketHandler_h

#include "ANetwork.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <thread>

class PacketHandler: ANetwork {
private:
    std::thread               _thread;
    std::vector<std::string>  _stack;
    
    void    readPacket();
public:
    PacketHandler(int Socket);
    ~PacketHandler();

    std::string getPacket();
    void    sendPacket(std::string);
};
#endif /* PacketHandler_h */
