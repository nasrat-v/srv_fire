//
// Created by nasrat_v on 15/03/18.
//

#include "../include/BusinessLogicManager.hh"

BusinessLogicManager::BusinessLogicManager(PacketHandler networkCpy, const std::string& _id): _network(networkCpy), _manager(_network)
{
    id = _id;
    std::cout << id << std::endl;
    running = true;
    _timer = std::thread(&BusinessLogicManager::time, this);
    _maxFd = -1;
}

void BusinessLogicManager::setAllFd() {
    FD_ZERO(&_rfds);
    if (_network.getEmbeded() != -1) {
        FD_SET(_network.getEmbeded(), &_rfds);
        if (_network.getEmbeded() >= _maxFd)
            _maxFd = _network.getEmbeded() + 1;
    }
    if (_network.getCamera() != -1) {
        FD_SET(_network.getCamera(), &_rfds);
        if (_network.getCamera() >= _maxFd)
            _maxFd = _network.getCamera() + 1;
    }
    if (_network.getIA() != -1) {
        FD_SET(_network.getIA(), &_rfds);
        if (_network.getIA() >= _maxFd)
            _maxFd = _network.getIA() + 1;
    }
}

int BusinessLogicManager::readEmbedded(int fd) {
    std::string cmd;

    if (!((cmd = _network.getPacket(fd)) == "ERROR")) {
        readCommand(cmd);
        return fd;
    }
    close(fd);
    fd = -1;
    return fd;
}

void BusinessLogicManager::readCommand(std::string cmd) {

        _manager.emptyData();
        if (!_manager.analyseCommand(cmd))
            Log.log("Error analyzing command : " +  cmd, id);
}

void        BusinessLogicManager::run(char **env)
{
    _camera = std::thread(&BusinessLogicManager::cameraHandler, this, env);

    while (running) {
/*        setAllFd();
        if (select(_maxFd, &_rfds, nullptr, nullptr, nullptr)) {
            setAllFd();
            if (_network.getEmbeded() != -1 && FD_ISSET(_network.getEmbeded(), &_rfds)) {
                readEmbedded(_network.getEmbeded());
            }
            else if (_network.getCamera() != -1 && FD_ISSET(_network.getCamera(), &_rfds)) {
                readEmbedded(_network.getCamera());
            }
            else if (_network.getIA() != -1 && FD_ISSET(_network.getIA(), &_rfds)) {
                readEmbedded(_network.getIA());
            }
        }*/
        _network.setEmbeded(readEmbedded(_network.getEmbeded()));
    }
}

void BusinessLogicManager::time() {

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    while (running) {
        end = std::chrono::system_clock::now();
        if (( std::chrono::duration<double>(end-start)).count() > 5) {
            _network.sendPacket("Update Allsensor", _network.getEmbeded());
            start = std::chrono::system_clock::now();
        }
        if (( std::chrono::duration<double>(end-start)).count() > 10) {
            start = std::chrono::system_clock::now();
        }
    }
}

void BusinessLogicManager::analyse(char **env)
{
    char    *str;

    str = new char[std::to_string(_network.get_embeddedId()).size() + 1];
    for (int n = 0; n < std::to_string(_network.get_embeddedId()).size(); n++) {
        str[n] = std::to_string(_network.get_embeddedId()).at(n);
    }
    char    *argv[] = {"./ia", "--debug", "--track", "--network-id", str, NULL};

    execve(argv[0], argv , env);
    if (running)
        return analyse(env);
}

void BusinessLogicManager::exit() {
    kill(_pid, SIGINT);
    _network.sendPacket("EXIT", _network.getEmbeded());
    _network.quit();
//    _timer.join();
    running = false;
}

BusinessLogicManager::~BusinessLogicManager()
= default;

bool BusinessLogicManager::isRunning() {
    return running;
}

void BusinessLogicManager::setId(const std::string& _id) {
    id = _id;
}

std::string BusinessLogicManager::getId() {
    return id;
}

void BusinessLogicManager::setCamera(socklen_t len, struct sockaddr_in _udpCliInf, int _udpConnect) {
    _network.setCamera(_udpConnect);
    _network.set_udpCliInf(_udpCliInf);
    _network.setLen(len);
}

void BusinessLogicManager::addToPile(std::string str) {
    _pile.push_back(str);

}

void BusinessLogicManager::recordBinary(char *binary) {
//    _manager.recordContent(binary);
}

void BusinessLogicManager::cameraHandler(char **env) {

    if ((_pid = fork()) == -1)
        Log.log("Unable to fork for camera");
    if (_pid == 0)
        return analyse(env);

    while (running) {
/*        setAllFd();
        if (select(_maxFd, &_rfds, nullptr, nullptr, nullptr)) {
            setAllFd();
            if (_network.getEmbeded() != -1 && FD_ISSET(_network.getEmbeded(), &_rfds)) {
                readEmbedded(_network.getEmbeded());
            }
            else if (_network.getCamera() != -1 && FD_ISSET(_network.getCamera(), &_rfds)) {
                readEmbedded(_network.getCamera());
            }
            else if (_network.getIA() != -1 && FD_ISSET(_network.getIA(), &_rfds)) {
                readEmbedded(_network.getIA());
            }
        }*/
        while (_network.getCamera() == -1);
        _network.setCamera(readEmbedded(_network.getCamera()));
    }
/*    while (running) {
        if  (_pile.size() > 0) {
             readCommand(_pile.at(0));
            _pile.erase(_pile.begin());
        }
    } */
}
