//
// Created by nasrat_v on 29/05/18.
//

#include "../header/Log.hh"

Log::Log() = default;

Log::~Log() = default;

/**
 * Static function, can be called everywhere.
 * Get current time to format: DAY MONTH NUM_DAY HOUR:MIN:SEC YEAR.
 * Hour are in 24h format
 * @return Current time
 */
const std::string   Log::getTime()
{
    std::time_t     time_now;

    time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return (std::ctime(&time_now));
}

/**
 * Static function, can be called everywhere.
 * Log something in a log file
 * @param complementary_msg Additional message to display
 * @param file_path Special filepath, if empty the default file path is the macro LOGFILE_PATH
 */
void                Log::logSomething(const std::string &complementary_msg, const std::string &file_path, bool error)
{
    std::fstream    file(file_path, std::fstream::out | std::fstream::app);

    file << ("[" + getTime() + "\t" + complementary_msg + "]") << std::endl << std::endl;
    if (!error)
        std::cout << "[" << complementary_msg << "]" << std::endl;
    file.close();
}