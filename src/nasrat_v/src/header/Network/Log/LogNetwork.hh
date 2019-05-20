#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

# define SUCCESS			(ERR)1
# define FILE_ERROR			(ERR)~0
# define LOGFILE_NAME		"../output/log/log-network.txt"

typedef short			ERR;
static bool				_tryStatus = false;
static bool             _logActive = true;
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