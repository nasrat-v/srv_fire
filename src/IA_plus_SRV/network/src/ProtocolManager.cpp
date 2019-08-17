//
// Created by Alexandre Bouvier on 12/03/2019.
//

#include "../include/ProtocolManager.hh"

ProtocolManager::ProtocolManager(PacketHandler network): _network(network) {
    _funcPtr["name"] = std::bind(&ProtocolManager::recordSensor, this);
    _funcPtr["Image"] = std::bind(&ProtocolManager::recordImage, this);
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

bool ProtocolManager::recordSensor() {
    _data["session_id"] = _network.get_sessionId();
    Log.log(_data.dump(), std::to_string(_network.get_embeddedId()));
    _data = nlohmann::json::parse(_network.sendRequest("Sensor/create.php", _data.dump()));
    if (_data["code"] == "200")
        return true;
    return false;
}

bool ProtocolManager::recordImage() {
    if (_data.find("Size") == _data.end()) {
        Log.log("Missing size in Json image packet", std::to_string(_network.get_embeddedId()));
        return false;
    }
    toRead = _data["Size"];
    content = new char[toRead];
    _contentbuff = 0;
    return true;
}

void ProtocolManager::emptyData() {
    if (_data.size() > 0)
        _data.erase(_data.begin(), _data.end());
}

bool ProtocolManager::recordContent(char *buffer) {
    FILE*   file;
    static std::string path = "../imageAnalyzing/output/image/tmp";

    std::cout << "-------" << std::endl;
    write(0, buffer, 50000);
    std::cout << std::endl << "-------" << std::endl;
    std::cout << "sizeReaded : " << _contentbuff << std::endl;
    for (int i =0; i < 50000 && _contentbuff + i < toRead; i++) {
        this->content[_contentbuff + i] = buffer[i];
    }
    _contentbuff += 50000;
    std::cout << "concat" << std::endl;
    if (_contentbuff > toRead) {
        path += std::to_string(rand() % 10 + 48);
        Log.log("Saving image to path : " + path, std::to_string(_network.get_embeddedId()));
        file = fopen((path + ".png").c_str(), "wb");
        fwrite(this->content, 1, toRead, file);
        fflush(file);
        fclose(file);
            _network.sendPacket(path + ".png", _network.getIA());
            emptyData();
            _data["path"] = path;
            _data["session_id"] = _network.get_sessionId();
            _data["online"] = true;
            _data["date"] = _network.getDateFormat();
            std::cout << _data << std::endl;
            _data = nlohmann::json::parse(_network.sendRequest("Camera/create.php", _data.dump()));
        }
    return true;
}
