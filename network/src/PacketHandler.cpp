//
//  Packet.cpp
//  srv-fire
//
//  Created by Alexandre Bouvier on 13/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#include <cstring>
#include <fcntl.h>
#include "../include/PacketHandler.h"

PacketHandler::PacketHandler(const std::string& url) : ANetwork(url)
{
    _embededSocket = -1;
    _cameraSocket = -1;
    _iaSocket = -1;
}
bool PacketHandler::initAPIData(std::string embededId) {

    if (!getDataBaseEmebedded(embededId))
        return false;
    return createDataBaseSession();
}

bool PacketHandler::getDataBaseEmebedded(std::string embededId) {
    std::stringstream  ss;
    nlohmann::json                      response;
    std::string                         ApiAnswer;
    nlohmann::json                      querry;

    querry["user_id"] = _userId;
    if (embededId == "-1") {
        querry["user_id"] = _userId;
        ss << querry;
        ApiAnswer = sendRequest("Embedded/create.php", ss.str());
        ApiAnswer = formatJsonForTab(ApiAnswer);
        std::cout << ApiAnswer << std::endl;
        response = nlohmann::json::parse(ApiAnswer);
        if (response.find("id") == response.end()) {
            Log.log("Failed to create Embedded on database");
            return false;
        }
        _embeddedId = response["id"];
        sendPacket(ApiAnswer, getEmbeded());
    }
    else {
        response = nlohmann::json::parse(sendRequest("Embedded/embedded.php?id=" + embededId));
        if (response.find("id") == response.end()) {
            Log.log("Failed to log Embedded on databse", embededId);
            return false;
        }
    }
    _embeddedId = response["id"];
    return true;
}

bool PacketHandler::createDataBaseSession() {
    nlohmann::json  response;
    nlohmann::json  querry;
    std::stringstream  ss;

    querry["embedded_id"] = _embeddedId;
    querry["start"] = getDateFormat();
    querry["finish"] = getDateFormat();
    querry["location"] = "N/A";
    ss << querry;
    response = nlohmann::json::parse(sendRequest("Session/create.php", ss.str()));
    if (response.end() == response.find("id")) {
        Log.log("Failed to initialize session on Database", std::to_string(_embeddedId));
        return false;
    }
    _sessionId = response["id"];
    return true;
}

bool PacketHandler::initAPIConnection() {
    userInf["user_name"] = "Scaduto";
    userInf["password"] = "test";
    std::stringstream  ss;
    ss << userInf;
    std::string tmp = sendRequest("/connect.php",  ss.str());
    userInf = nlohmann::json::parse(tmp);
    if (userInf.find("token") != userInf.end()) {
        _tokenJWT = userInf["token"];
        _userId = userInf["user_id"];
        return true;
    }
    Log.log("Failed to connect to API");
    return (false);
}

std::string  PacketHandler::getPacket(int fd)
{
    size_t size;
    size_t pos;
    std::string back;
    char    buffer[2];

    memset(buffer, 0, 2);
    while ((size = static_cast<size_t>(read(fd, buffer, 1))) > 0)
    {
        back += std::string(buffer);
        memset(buffer, 0, 2);
        if ((pos = back.find('\n')) != std::string::npos) {
            back.erase(pos);
            return (back);
        }
    }
    return ("ERROR");
}

void    PacketHandler::sendPacket(std::string toSend, int fd)
{
    write(fd, std::string(toSend + "\n").c_str(), toSend.size() + 1);
}

std::string PacketHandler::sendRequest(const std::string road, const std::string& body) {
    curlpp::Cleanup clean;
    curlpp::Easy r;
    std::string     back;
    std::list<std::string>  header;

    if (!_tokenJWT.empty())
        header.push_back("Authorization: " + _tokenJWT);
    if (road.find("?") != std::string::npos)
        header.push_back("TYPE: " + std::string("GET"));
    if (road.find("update") != std::string::npos)
        header.push_back("TYPE: " + std::string("PUT"));
    Log.log(_url + road, std::to_string(_embeddedId));
    r.setOpt(new curlpp::options::Url(_url + road));
    if (!_tokenJWT.empty())
        r.setOpt(new curlpp::options::HttpHeader(header));
    r.setOpt(new curlpp::options::PostFields(body));
    r.setOpt(new curlpp::options::PostFieldSize(body.length()));

    std::ostringstream response;
    r.setOpt(new curlpp::options::WriteStream(&response));

    r.perform();
    back = response.str();
    if (back.at(back.size() - 1) == '\n')
        back.erase(back.size() - 1);
    Log.log(back, std::to_string(_embeddedId));
    return back;
}

void PacketHandler::quit() {
    if (_embededSocket > 0)
        close(_embededSocket);
    if (_iaSocket > 0)
        close(_iaSocket);
    if (_cameraSocket > 0)
        close(_cameraSocket);
}

std::string PacketHandler::getDateFormat() {
    time_t rawtime;
    struct tm * timeinfo;
    char dateAff [83];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime(dateAff, 83,"%Y-%m-%d %H:%M:%S+00",timeinfo);
    return dateAff;
}

const int &PacketHandler::get_embeddedId() const {
    return _embeddedId;
}

const int &PacketHandler::get_sessionId() const {
    return _sessionId;
}

int PacketHandler::recv_message(char *msg, size_t max_size) {
    len = sizeof(_udpCliInf);
    return recvfrom(_udpConnect, (char *)msg, max_size, MSG_WAITALL, ( struct sockaddr *) &_udpCliInf, &len);
}

int PacketHandler::send_message(char *msg) {
    return sendto(_udpConnect, (const char *)msg, strlen(msg), 0, (const struct sockaddr *) &_udpCliInf, len);
}

void PacketHandler::setLen(socklen_t _len) {
    this->len = _len;
}

void PacketHandler::set_udpCliInf(const sockaddr_in &udpCliInf) {
    this->_udpCliInf = udpCliInf;
}

std::string PacketHandler::formatJsonForTab(std::string ApiAnswer) {
    std::string ret = "";
    std::string tmp = ApiAnswer;
    size_t  pos_s;
    size_t  pos_e;

    while ((pos_s = ApiAnswer.find("\"{")) != std::string::npos) {
        ret += ApiAnswer.substr(0, pos_s);
        ret += '[';
        if ((pos_e = ApiAnswer.find("}\"")) != std::string::npos) {
            ret += ApiAnswer.substr(pos_s + 2, pos_e - pos_s - 2);
            ret += ']';
            ApiAnswer = ApiAnswer.erase(0, pos_e + 2);
        }
        else {
            return tmp;
        }
    }
    ret += ApiAnswer;
    return ret;
}

const std::string &PacketHandler::get_loc() const {
    return _loc;
}

void PacketHandler::set_loc(const std::string &_loc) {
    PacketHandler::_loc = _loc;
}

bool    PacketHandler::initSSHConnection() {
}