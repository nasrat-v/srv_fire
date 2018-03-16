//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_ERROR_HH__
# define __OPENCV_TEST_ERROR_HH__

#include <iostream>
#include <fstream>

# define LOGFILE_PATH   "ErrorLog.txt"

class Error
{
public:
    enum class      ErrorType
    {
        OPEN_IMG,
        UNKNOWN_ERROR
    };

    static void         logError(const ErrorType &type);
    static void         logError(const ErrorType &type, const std::string &complementary_msg);

private:
    Error();
    ~Error();
    static const std::string   getMessage(const ErrorType &type);
    static const std::string   getTime();
};

#endif /* !__OPENCV_TEST_ERROR_HH__ */
