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
#include "../../Utilitary/loger.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>
#include <thread>
#include <stdlib.h>
#include <time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>

extern loger Log;

class PacketHandler: public ANetwork {
private:
    socklen_t                           len;
public:
    void setLen(socklen_t len);

    void set_udpCliInf(const sockaddr_in &_udpCliInf);

private:
    struct sockaddr_in                  _udpCliInf;
    int                                 _udpConnect;
    nlohmann::json                      userInf;
    std::string                         _tokenJWT;
    int                                 _userId;
    int                                 _embeddedId;
    int                                 _sessionId;
    std::string                         _loc;
public:
    const std::string &get_loc() const;

    void set_loc(const std::string &_loc);

private:
    std::string     formatJsonForTab(std::string);

public:
    explicit PacketHandler(const std::string& url);

    std::string getPacket(int fd);

    void    sendPacket(std::string, int);
    std::string sendRequest(const std::string road, const std::string& body = "");

    int recv_message(char *msg, size_t max_size);
    int send_message(char *msg);


    bool    initAPIConnection();
    bool    initAPIData(std::string EmbededId);
    bool           initSSHConnection();
    bool           getDataBaseEmebedded(std::string);
    bool           createDataBaseSession();


    std::string     getDateFormat();
    const int &get_embeddedId() const;

    const int &get_sessionId() const;

    void    quit();
};
#endif /* PacketHandler_h */
