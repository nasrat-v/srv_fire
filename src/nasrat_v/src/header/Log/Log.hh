//
// Created by nasrat_v on 29/05/18.
//

#ifndef __OPENCV_SRV_LOG_HH__
# define __OPENCV_SRV_LOG_HH__

# define DEBUGANAL_ACTIVE   false
# define LOGFILE_PATH       "../output/log/log.txt"

#include <iostream>
#include <fstream>
#include <chrono>

static bool                     __attribute__((unused))_logActive = false;

class Log
{
public:
    static void                 logSomething(const std::string &complementary_msg = "", const std::string &file_path = LOGFILE_PATH, bool error = false);
    static void                 logMsg(const std::string &complementary_msg = "", const std::string &file_path = LOGFILE_PATH, bool error = false);

private:
    Log() = default;
    ~Log() = default;
    static const std::string    getTime();
};

#endif /* !__OPENCV_SRV_LOG_HH__ */
