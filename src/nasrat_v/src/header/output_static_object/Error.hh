//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_ERROR_HH__
# define __OPENCV_TEST_ERROR_HH__

#include "Log.hh"

# define ERROR_LOGFILE_PATH   "../output/log/error/error_log.txt"

class Error
{
public:
    enum class      ErrorType
    {
        UNKNOWN_ERROR,
        OPEN_IMG,
        TRUNCATED_IMG
    };

    static void                 logError(const ErrorType &type, const std::string &complementary_msg = "");

private:
    /* Methods */
    Error();
    ~Error();
    static const std::string    getMessage(const ErrorType &type);
};

#endif /* !__OPENCV_TEST_ERROR_HH__ */
