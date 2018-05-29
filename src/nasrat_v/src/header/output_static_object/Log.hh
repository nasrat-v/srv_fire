//
// Created by nasrat_v on 29/05/18.
//

#ifndef __OPENCV_SRV_LOG_HH__
# define __OPENCV_SRV_LOG_HH__

#include <iostream>
#include <fstream>
#include <chrono>

# define LOGFILE_PATH   "../output/log/log.txt"

class Log
{
public:
    static void                 logSomething(const std::string &complementary_msg = "", const std::string &file_path = LOGFILE_PATH);

private:
    Log();
    ~Log();
    static const std::string    getTime();
};

#endif /* !__OPENCV_SRV_LOG_HH__ */
