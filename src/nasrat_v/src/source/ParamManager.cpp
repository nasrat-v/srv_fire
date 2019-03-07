//
// Created by nasrat_v on 3/7/19.
//

#include "../header/ParamManager.hh"

ParamManager::ParamManager()
{
    _idNetwork = "no_id";
}

ParamManager::~ParamManager() = default;

const std::vector<std::string> ParamManager::convertCharStarToVectorOfString(const char **array)
{
    return (std::vector<std::string>(array, array + (strlenTab(array))));
}

int ParamManager::strlenTab(const char **array)
{
    int i = -1;

    while (array[++i]);
    return (i);
}

ParamManager::paramMode ParamManager::findParams(const char **av)
{
    uint16_t mode = paramMode::NO_PARAM;
    std::vector<std::string> args = convertCharStarToVectorOfString(av);
    auto it = args.begin();

    while (it != args.end())
    {
        if (*it == NETWORK_ARG)
        {
            mode |= paramMode::NETWORK_MODE;
            _idNetwork = *(++it);
        }
        if (*it == DEBUG_ARG)
            mode |= paramMode::DEBUG_MODE;
        it++;
    }
    return ((paramMode)mode);
}

const std::string &ParamManager::getIdNetwork() const
{
    return (_idNetwork);
}
