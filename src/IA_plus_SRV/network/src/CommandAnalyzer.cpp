#include <utility>

#include <utility>

//
// Created by Alexandre Bouvier on 17/11/2018.
//

#include "../include/CommandAnalyzer.hh"

CommandAnalyzer::CommandAnalyzer(std::map<std::string, BusinessLogicManager*>& cli, std::map<std::string, std::thread>& thread) : _cli(cli), _thread(thread) {
    initCmd();
}

void CommandAnalyzer::killNotRunningThread() {
    for (auto it  : _cli) {
        if (!it.second->isRunning()) {
//            it = _cli.erase(it);
        }
    }
}

void CommandAnalyzer::killAllThread() {
    for (auto it  : _cli)
        it.second->exit();
}

void CommandAnalyzer::killOneThread(std::string id) {
    if (_cli.find(id) == _cli.end()) {
        std::cout << "Wrong ID" << std::endl;
        Log.log("Wrong ID");
        return ;
    }
    _cli[id]->exit();
}

bool CommandAnalyzer::treatCmd(int _fdConnect, std::string cmd) {
    pid_t thread;
    std::string arg;
    size_t pos;
    Log.log(cmd);

    if ((pos = cmd.find(' ')) != std::string::npos) {
        arg = std::string(cmd).substr(pos + 1, cmd.size() - pos + 1);
        cmd = std::string(cmd).substr(0, pos);
    }
    for (auto it : _cmdList)
        if (it.first == cmd) {
                return it.second(arg);
        }
    Log.log("Unknow cmd");
    return true;
}

void CommandAnalyzer::initCmd() {
    _cmdList["EXIT"] = std::bind(&CommandAnalyzer::cmdEXIT, this, std::string());
    _cmdList["LIST"] = std::bind(&CommandAnalyzer::cmdListEmbedded, this, std::string());
    _cmdList["KILL"] = std::bind(&CommandAnalyzer::cmdKill, this, std::string());
}

bool CommandAnalyzer::cmdEXIT(std::string arg) {
    killAllThread();
    killNotRunningThread();
    return false;
}

bool CommandAnalyzer::cmdListEmbedded(std::string arg) {
    for (auto it : _cli)
        std::cout << it.second->getId() << std::endl;
    return true;
}

bool CommandAnalyzer::cmdKill(std::string arg) {
    killOneThread(std::move(arg));
    return true;
}
