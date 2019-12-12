
#ifndef __LOGNETWORK_HH__
#define __LOGNETWORK_HH__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

# define DEBUGNET_ACTIVE	false
# define SUCCESS			(ERR)1
# define FILE_ERROR			(ERR)~0
# define LOGFILE_NAME		"../output/log/log-network.txt"

typedef short			ERR;
static bool				__attribute__((unused))_tryStatus = false;
static bool             __attribute__((unused))_logNetActive = true;
static std::fstream		_logFile;

class LogNetwork
{
public:
	static void			openLogFile(const char *filePath);
	static void			closeLogFile();
	static void			logSuccessMsg(const std::string &msg);
	static void			logFailureMsg(const std::string &msg);
	static void			logInfoMsg(const std::string &msg);
	static void			logTryMsg(const std::string &msg);
	static void			logSomething(const std::string &msg);
    static void         setLogActive(bool log);

private:
    LogNetwork() = default;
	~LogNetwork() = default;
};

#endif /* !__LOGNETWORK_HH__ */