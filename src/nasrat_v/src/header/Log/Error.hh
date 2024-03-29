//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_ERROR_HH__
# define __OPENCV_TEST_ERROR_HH__

# define ERROR_LOGFILE_PATH     "../output/log/log.txt"
# define MIN_FRAME_VID          2

#include "Log.hh"

class Error
{
public:
    enum class      ErrorType
    {
        NOPE,
        UNKNOWN,
        OPEN_IMG,
        OPEN_VID,
        TRUNCATED_VID,
        MISSING_FRAME_INFOS,
        MISSING_INIT,
        NO_CONTOUR,
        THREAD,
        NETWORK,
        DEBUG_STOP,
        TRUNCATED_IMG_NETWORK
    };

    static void                 logError(const ErrorType &type, const std::string &complementary_msg = "");
    static void                 logErrorAbort(const ErrorType &type, const std::string &complementary_msg = "");

private:
    /* Methods */
    Error() = default;
    ~Error() = default;
    static const std::string    getMessage(const ErrorType &type);
};

#endif /* !__OPENCV_TEST_ERROR_HH__ */
