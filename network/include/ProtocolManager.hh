//
// Created by Alexandre Bouvier on 12/03/2019.
//

#ifndef IA_PROTOCOLMANAGER_HH
#define IA_PROTOCOLMANAGER_HH


#include "PacketHandler.h"
#include "../../Utilitary/loger.hpp"
#include <functional>

extern loger Log;

class ProtocolManager {
private:
    long             toRead;
    char            *content;
    std::string     _lastCmd;
    std::string     name;
    PacketHandler   &_network;
    std::map<std::string, std::function<bool()>>   _funcPtr;
    nlohmann::json             _data;

    bool    recordSensor();
    bool    recordImage();
    bool    recordColor();
    bool    recordLocalisation();

    bool    sendImage();
    bool    sendColor();
public:
    bool    recordContent();
    explicit ProtocolManager(PacketHandler &network);

    bool    analyseCommand(std::string cmd);

    void    emptyData();
};


#endif //IA_PROTOCOLMANAGER_HH
