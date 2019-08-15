//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__
# define __OPENCV_TEST_BUSINESSLOGICMANAGER_HH__

# define FILE_PATH  "/home/nasrat_v/Images/blue.jpg"
# define X_IMAGE_CLE    640
# define Y_IMAGE_CLE    480

#include "PacketHandler.h"
#include "ProtocolManager.hh"
#include "../../Utilitary/loger.hpp"
#include <thread>
#include <signal.h>

extern loger Log;

class BusinessLogicManager
{
public:
    PacketHandler       _network;

    BusinessLogicManager(PacketHandler networkCpy, const std::string& _id);
    ~BusinessLogicManager();

    void                run(char **env);
    void                exit();

    bool                isRunning();
    void                setId(const std::string&);
    std::string                 getId();

    void    readCommand(std::string cmd);


    void    setCamera(socklen_t len, struct sockaddr_in _udpCliInf, int _udpConnect);
    void    recordBinary(char*);
    void    addToPile(std::string);
private:
    ProtocolManager             _manager;
    std::string                 id;
    bool                        running;
    std::vector<std::string>    _pile;

    int                         _pid;
    std::thread                 _timer;
    std::thread                 _camera;

    fd_set                      _rfds;
    int                       _maxFd;

    void time();

    void    setAllFd();
    int    readEmbedded(int fd);
    void    cameraHandler(char **env);

    void analyse(char **env);
};

#endif /* !__OPENCV_TEST_BUSINESSLOGICMANAGER_HH__ */
