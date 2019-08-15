//
// Created by Alexandre Bouvier on 12/03/2019.
//

#include "../include/ProtocolManager.hh"

ProtocolManager::ProtocolManager(PacketHandler &network): _network(network) {
    _funcPtr["name"] = std::bind(&ProtocolManager::recordSensor, this);
    _funcPtr["location"] = std::bind(&ProtocolManager::recordLocalisation, this);
    _funcPtr["Image"] = std::bind(&ProtocolManager::recordImage, this);
    _funcPtr["Color"] = std::bind(&ProtocolManager::recordColor, this);
}

bool ProtocolManager::analyseCommand(std::string Command) {
    size_t  pos;

    std::cout << Command << std::endl;
    _data = nlohmann::json::parse(Command);
    for (auto &key : _funcPtr) {
        for (auto cmd = _data.begin(); cmd != _data.end(); cmd++) {
            if (key.first == cmd.key())
                return key.second();
        }
    }
    return false;
}

bool ProtocolManager::recordLocalisation() {
    _network.set_loc(_data["location"]);
    _data["session_id"] = _network.get_sessionId();
    _data = nlohmann::json::parse(_network.sendRequest("Session/update.php", _data.dump()));
    if (_data["code"] == "200")
        return true;
    return false;
}

bool ProtocolManager::recordSensor() {
    _data["session_id"] = _network.get_sessionId();
    Log.log(_data.dump(), std::to_string(_network.get_embeddedId()));
    _data = nlohmann::json::parse(_network.sendRequest("Sensor/create.php", _data.dump()));
    if (_data["code"] == "200")
        return true;
    return false;
}

bool ProtocolManager::recordColor() {
    if (_data.find("Size") == _data.end()) {
        Log.log("Missing size in Json image packet", std::to_string(_network.get_embeddedId()));
        return false;
    }
    toRead = _data["Size"];
    content = new char[toRead];
    _lastCmd = "Color";
    return recordContent();
}

bool ProtocolManager::recordImage() {
/*    if (_contentbuff > 0 && _contentbuff < toRead) {
        sendImage("notFull");
    } */
    if (_data.find("Size") == _data.end()) {
        Log.log("Missing size in Json image packet", std::to_string(_network.get_embeddedId()));
        return false;
    }
    toRead = _data["Size"];
    content = new char[toRead];
    _lastCmd = "Image";
    return recordContent();
}

void ProtocolManager::emptyData() {
    if (_data.size() > 0)
        _data.erase(_data.begin(), _data.end());
}

bool ProtocolManager::sendColor() {
    static std::string path = "../imageAnalyzing/output/image/img";
    FILE*   file;

    Log.log("Saving color to path : " + path + name, std::to_string(_network.get_embeddedId()));
    file = fopen((path + name + ".clr").c_str(), "wb");
    fwrite(this->content, 1, toRead, file);
    fflush(file);
    fclose(file);
    _network.sendPacket(path + name + ".clr", _network.getIA());
    return true;
}

bool ProtocolManager::sendImage() {
    static std::string path = "../imageAnalyzing/output/image/img";
    FILE*   file;

    name += std::to_string(rand() % 10 + 48);
    Log.log("Saving image to path : " + path + name + ".png", std::to_string(_network.get_embeddedId()));
    file = fopen((path + name + ".png").c_str(), "wb");
    fwrite(this->content, 1, toRead, file);
    fflush(file);
    fclose(file);
    _network.sendPacket(path + name + ".png", _network.getIA());
    emptyData();
    _data["path"] = "fire_serv/"  + name + ".png";
    _data["session_id"] = _network.get_sessionId();
    _data["date"] = _network.getDateFormat();
    std::cout << _data << std::endl;
//    _data = nlohmann::json::parse(_network.sendRequest("Camera/create.php", _data.dump()));
    return true;
}

bool ProtocolManager::recordContent() {
    char        *buff = new char [1];

    for (int i = 0; i < toRead; i++) {
        memset(buff, 0, 1);
        read(_network.getCamera(), buff, 1);
        content[i] = *buff;
    }
    if (_lastCmd == "Image")
        return sendImage();
    else if (_lastCmd == "Color")
        return sendColor();
}
