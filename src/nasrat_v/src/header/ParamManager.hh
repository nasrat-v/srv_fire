//
// Created by nasrat_v on 3/7/19.
//

#ifndef OPENCV_SRV_PARAMMANAGER_HH
#define OPENCV_SRV_PARAMMANAGER_HH

# define NETWORK_ARG    "--network-id"
# define DEBUG_ARG      "--debug"

#include <iostream>
#include <vector>
#include <cstring>

class ParamManager
{
public:
    ParamManager();
    ~ParamManager();

    enum    paramMode
    {
        NO_PARAM = 0b0000'0000'0000'0000,
        NETWORK_MODE = 0b0000'0000'0000'0001,
        DEBUG_MODE = 0b0000'0000'0000'0010,
        ALL = 0b1111'1011'1111'1111
    };

    ParamManager::paramMode         findParams(const char **av);
    const std::string               &getIdNetwork() const;

private:
    int                             strlenTab(const char **array);
    const std::vector<std::string>  convertCharStarToVectorOfString(const char **array);
    std::string                     _idNetwork;
};

#endif //OPENCV_SRV_PARAMMANAGER_HH
