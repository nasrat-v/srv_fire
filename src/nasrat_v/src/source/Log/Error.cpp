//
// Created by nasrat_v on 15/03/18.
//

#include "../../header/output_static_object/Error.hh"

Error::Error() = default;

Error::~Error() = default;

/**
 * Gives the appropriate message for each error type
 * @param type Enum type of the error
 * @return Appropriate message for the error type
 */
const std::string   Error::getMessage(const ErrorType &type)
{
    switch (type)
    {
        case (ErrorType::NO_ERROR):
            return ("No error");
        case (ErrorType::UNKNOWN_ERROR):
            return ("Unknown error");
        case (ErrorType::OPEN_VID):
            return ("Could not open video");
        case (ErrorType::TRUNCATED_VID):
            return ("Video must contain a minimum of " + std::to_string(MIN_FRAME_VID) + " frames");
        case (ErrorType::MISSING_FRAME_INFOS):
            return ("Missing frame infos. Frame need to be initialized before being analyzed");
        case (ErrorType::MISSING_INIT):
            return ("Missing initialization before analyse");
        case (ErrorType::NO_CONTOUR):
            return ("Missing contour");
    };
    return ("");
}

/**
 * Static function, can be called everywhere.
 * Log an error in the error log file and then abort the program.
 * The log file path is defined by the macro ERROR_LOGFILE_PATH
 * @param type Enum type of the error
 * @param complementary_msg Additional error message
 */
void                Error::logErrorAbort(const Error::ErrorType &type, const std::string &complementary_msg)
{
    logError(type, complementary_msg);
    abort();
}


/**
 * Static function, can be called everywhere.
 * Log an error in the error log file.
 * The log file path is defined by the macro ERROR_LOGFILE_PATH
 * @param type Enum type of the error
 * @param complementary_msg Additional error message
 */
void                Error::logError(const Error::ErrorType &type, const std::string &complementary_msg)
{
    std::string     msg = (getMessage(type) + " " + complementary_msg);

    Log::logSomething(msg, ERROR_LOGFILE_PATH, true);
    std::cerr << "[" << msg << "]" << std::endl;
}