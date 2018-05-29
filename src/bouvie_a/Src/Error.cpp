//
// Created by nasrat_v on 15/03/18.
//

#include <chrono>
#include "../Include/Error.hh"

Error::Error()
{
}

Error::~Error()
{
}

const std::string   Error::getMessage(const ErrorType &type)
{
    switch (type)
    {
        case (ErrorType::UNKNOWN_ERROR):
            return ("Unknown error");
        case (ErrorType::OPEN_IMG):
            return ("Could not open image");
    };
}

const std::string   Error::getTime()
{
    std::time_t     time_now;

    time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return (std::ctime(&time_now));
}

void                Error::logError(const Error::ErrorType &type, const std::string &complementary_msg)
{
    std::fstream    file(LOGFILE_PATH, std::fstream::out | std::fstream::app);

    file << "[" << getTime() << "\t" << getMessage(type) << " : " << complementary_msg << "]" << std::endl << std::endl;
    file.close();
}
