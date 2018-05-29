//
// Created by nasrat_v on 15/03/18.
//

#include "../../header/output_static_object/Error.hh"

Error::Error()
{
}

Error::~Error()
{
}

/**
 * Gives the appropriate message for each error type
 * @param type Enum type of the error
 * @return Appropriate message for the error type
 */
const std::string   Error::getMessage(const ErrorType &type)
{
    switch (type)
    {
        case (ErrorType::UNKNOWN_ERROR):
            return ("Unknown error");
        case (ErrorType::OPEN_IMG):
            return ("Could not open image");
        case (ErrorType::OPEN_DIR):
            return ("Could not open directory");
        case (ErrorType::TRUNCATED_IMG):
            return ("Image is truncated, could not analyse it");
    };
    return ("");
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

    Log::logSomething(msg, ERROR_LOGFILE_PATH);
    std::cerr << "[" << msg << "]" << std::endl;
}
