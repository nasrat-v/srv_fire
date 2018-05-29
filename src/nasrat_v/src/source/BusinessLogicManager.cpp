//
// Created by nasrat_v on 15/03/18.
//

#include "../header/BusinessLogicManager.hh"

BusinessLogicManager::BusinessLogicManager(int Socket): _network(Socket), _thread(&BusinessLogicManager::run, this)
{
}

BusinessLogicManager::~BusinessLogicManager()
{
    std::cout << "Thread Killed" << std::endl;
    _thread.detach();
}

float       *BusinessLogicManager::convertBuffToPalette(std::string buff)
{
    size_t              pos;
    float               temp;
    std::vector<float>  arrayFloat;

    while ((pos = buff.find(", ")) != std::string::npos)
    {
        temp = std::stof(buff.substr(0, pos));
        buff.erase(0, (pos + 2));
        arrayFloat.push_back(temp);
    }
    temp = std::stof(buff.substr(0, pos));
    buff.erase(0, (pos + 2));
    arrayFloat.push_back(temp);
    return (&arrayFloat[0]);
}

void        BusinessLogicManager::run()
{
    //std::string buff = "10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 60000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 30000, 20000";
    std::string buff = "";
    
    _network.sendPacket(*new std::string("Well Connected"));
    while ((buff = _network.getPacket()) != "QUIT")
    {
        if (buff != "")
        {
            _imageAnalyser.Analyse(Y_IMAGE_CLE, X_IMAGE_CLE, convertBuffToPalette(buff));
            buff = "";
        }
    }
    std::cout << buff << std::endl;
    delete(this);
}
