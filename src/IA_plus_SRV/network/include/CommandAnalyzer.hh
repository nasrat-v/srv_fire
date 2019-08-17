//
// Created by Alexandre Bouvier on 17/11/2018.
//

#ifndef IA_COMMANDANALYZER_HH
#define IA_COMMANDANALYZER_HH

#include "BusinessLogicManager.hh"

extern loger Log;

class CommandAnalyzer {
private:
    std::map<std::string, BusinessLogicManager*>& _cli;
    std::map<std::string, std::thread>&           _thread;
    std::map<std::string, std::function<bool(std::string)>> _cmdList;

    void    killAllThread();
    void    killOneThread(std::string id);

    void    initCmd();

    bool    cmdEXIT(std::string arg);
    bool    cmdListEmbedded(std::string arg);
    bool    cmdKill(std::string arg);
public:
    CommandAnalyzer(std::map<std::string, BusinessLogicManager*>& cli, std::map<std::string, std::thread>& thread);
    bool    treatCmd(int _fdConnect, std::string cmd);
    void    killNotRunningThread();

};


#endif //IA_COMMANDANALYZER_HH
