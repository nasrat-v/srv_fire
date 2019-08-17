//
//  connectionHandler.cpp
//  srv-fire
//
//  Created by Alexandre Bouvier on 12/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#include "../include/connectionHandler.h"

loger Log;

connectionHandler::connectionHandler() : commandManager(_cli, _thread), _network("http://109.10.72.8:81/API/")
{
    readProperties();
    if (!_network.initAPIConnection())
        Log.log("API connection failed");
}

connectionHandler::~connectionHandler()
{
    close(_tcpConnect);
}

void connectionHandler::readProperties() {

    std::ifstream    stream("../network/properties.txt");
    std::string      line;
    std::string      properties;
    std::size_t      pos;

    while (getline(stream, line)) {
        if ((pos = line.find('=')) != std::string::npos) {
            properties = line.substr(0, pos);
            std::string val  = line.substr(pos + 1, line.size());
            if (properties == "logOut") {
                int     logOut;
                if (val == "0")
                    Log.addFd(0);
                else if ((logOut = open(val.c_str(), O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR)) > 0) {
                    Log.addFd(logOut);
                }
            }
            else if (properties == "port") {
                _port = std::stoi(val, nullptr);
            }
            else if (properties == "maxCli")
                _maxCli = std::stoi(val, nullptr);
        }

    }
}

bool    connectionHandler::sendPacket(int fd, std::string toSend)
{
    if (fstat(fd, new struct stat()) == -1) {
        close(fd);
        return false;
    }
    write(fd, std::string(toSend + "\n").c_str(), toSend.size() + 1);
    return true;
}

std::string  connectionHandler::getPacket(int fd)
{
    size_t size;
    size_t pos;
    std::string back = "";
    char    buffer[4096];

    memset(buffer, 0, 4096);
    while ((size = static_cast<size_t>(read(fd, buffer, 4095))) > 0)
    {
        back += std::string(buffer);
        memset(buffer, 0, 4095);
        if ((pos = back.find('\n')) != std::string::npos) {
            back.erase(pos);
            return (back);
        }
    }
    return ("ERROR");
}

bool connectionHandler::connectNewCli(char **env) {
    _connectionThread.emplace_back(&connectionHandler::addCli, this, env);
    return true;
}

bool     connectionHandler::addCli(char **env)
{
    int newSock;
    std::string type;
    std::string id;

    if (!identifyClient(newSock, type, id))
        return false;
    _network.setEmbeded(newSock);
    _network.initAPIData(id);
    if (_cli.find(std::to_string(_network.get_embeddedId())) != _cli.end()) {
        if (type == "EMBEDDED")
            _cli[std::to_string(_network.get_embeddedId())]->_network.setEmbeded(newSock);
        else if (type == "IA")
            _cli[std::to_string(_network.get_embeddedId())]->_network.setIA(newSock);
    }
    else {
        if (type == "IA") {
            _network.setIA(_network.getEmbeded());
            _network.setEmbeded(-1);
        }
        else if (type != "EMBEDDED") {
            Log.log("Wrong client type ID : " + id);
            return false;
        }
        _cli[std::to_string(_network.get_embeddedId())] = new BusinessLogicManager(_network, std::to_string(_network.get_embeddedId()));
        _thread[std::to_string(_network.get_embeddedId())] = std::thread(&BusinessLogicManager::run, _cli[std::to_string(_network.get_embeddedId())], env);
    }
    Log.log(std::to_string(_network.get_embeddedId()) + " " + type);
    return (true);
}

bool connectionHandler::identifyClient(int &newSock, std::string &type, std::string &id) {
    struct sockaddr_in  cliInf{};
    int size = sizeof(cliInf);
    nlohmann::json      Json;
    size_t pos;

    if (!(newSock = accept(_tcpConnect, (struct sockaddr *)&cliInf, (socklen_t*)&size))) {
        Log.log("Failed to connect client");
        return (false);
    }
    Log.log("waiting for client identification");
    Json = nlohmann::json::parse(getPacket(newSock));
    type = Json["Type"];
    id = std::to_string((int)Json["Id"]);
    return true;
}

void    connectionHandler::setAllFd()
{
    FD_ZERO(&_rfds);
    FD_SET(_tcpConnect, &_rfds);
    FD_SET(0, &_rfds);
}


void    connectionHandler::start(char **env) {
    std::string read;

    setAllFd();
    Log.log("Server Launched");
    _udpThread = std::thread(&connectionHandler::udpHandler, this, env);
    while (select(_tcpConnect + 1, &_rfds, nullptr, nullptr, nullptr)) {
        if (FD_ISSET(_tcpConnect, &_rfds)) {
            Log.log("New cli connected");
            connectNewCli(env);
        }
        if (FD_ISSET(0, &_rfds)) {
            if ((read = getPacket(0)) == "ERROR")
                Log.log("Failed read command");
            if (!commandManager.treatCmd(_tcpConnect, read))
                return ;
        }
        commandManager.killNotRunningThread();
        setAllFd();
    }
}

bool connectionHandler::initConnection() {
    int     need = 1;

    if ((_tcpConnect = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        if (setsockopt(_tcpConnect, SOL_SOCKET, SO_REUSEADDR, &need, sizeof(int)) < 0) {
            Log.log("Error opening TCP socket");
            return false;
        }
    _tcpSrvInf.sin_family = AF_INET;
    _tcpSrvInf.sin_addr.s_addr = INADDR_ANY;
    if (_port == -1) {
        Log.log("Invalid port");
        return false;
    }
    _tcpSrvInf.sin_port = htons(_port);
    if (bind(_tcpConnect, (struct sockaddr*)&_tcpSrvInf, sizeof(_tcpSrvInf)) == -1) {
        Log.log("TCP Bind failed");
        return false;
    }
    listen(_tcpConnect, _maxCli);

    return true;
}

bool connectionHandler::initUDPConnection() {
    if ( (_udpConnect = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        Log.log("Error opening UDP socket");
        return false;
    }
    memset(&_udpSrvInf, 0, sizeof(_udpSrvInf));
    memset(&_udpCliInf, 0, sizeof(_udpCliInf));

    // Filling server information
    _udpSrvInf.sin_family    = AF_INET; // IPv4
    _udpSrvInf.sin_addr.s_addr = INADDR_ANY;
    _udpSrvInf.sin_port = htons(_port);

    // Bind the socket with the server address
    if (bind(_udpConnect, (const struct sockaddr *)&_udpSrvInf,
              sizeof(_udpSrvInf)) < 0 )
    {
        Log.log("UDP bind failed");
        return false;
    }
    return true;
}
void connectionHandler::udpHandler(char **env) {
    unsigned char     id;
    nlohmann::json jsonObj;
    char    *buffer;

    while (42) {
        buffer = new char[50000 + sizeof(unsigned char)];
        memset(buffer, 0, 50000 + sizeof(unsigned char));
        recv_message(buffer, 50000 + sizeof(unsigned char));
        Log.log("Activity on UDP socket");
        std::cout << buffer << std::endl;
        if (buffer[0] != '{') {
            id =((unsigned char*)buffer)[0];
            std::cout << (int)id << std::endl;
            buffer = buffer + sizeof(unsigned char);
            write(0, buffer, 50000);
            std::cout << std::endl;
            _cli[std::to_string((int)id)]->recordBinary(buffer);
        }
        else {
            jsonObj = nlohmann::json::parse(buffer);
            if (jsonObj.find("Id") == jsonObj.end()) {
                Log.log("No ID on UDP Command");
            } else {
                Log.log(jsonObj.dump(), std::to_string((int) jsonObj["Id"]));
                len = sizeof(_udpCliInf);
                if (jsonObj.find("Type") == jsonObj.end())
                    _cli[std::to_string(_network.get_embeddedId())]->addToPile(buffer);
                else
                    _cli[std::to_string((int) jsonObj["Id"])]->setCamera(len, _udpCliInf, _udpConnect);
            }
        }
    }
}

int connectionHandler::recv_message(char *msg, size_t max_size) {
    len = sizeof(_udpCliInf);
    return recvfrom(_udpConnect, (char *)msg, max_size, MSG_WAITALL, ( struct sockaddr *) &_udpCliInf, &len);
}