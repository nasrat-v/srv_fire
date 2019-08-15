//
// Created by Alexandre Bouvier on 16/09/2018.
//

#ifndef SRV_FIRE_LOGER_HPP

#define SRV_FIRE_LOGER_HPP

#include <string>
#include <vector>
#include <time.h>
#include <zconf.h>

class loger {
private:
    std::vector<int>                         _logFd;
    time_t date;

public:

    void addFd(int fd){
        _logFd.push_back(fd);
    }

    void log(std::string log, std::string id = ""){

        date = time(nullptr);
        std::string dateAff = ctime(&date);
        dateAff.erase(dateAff.find('\n'));
        for (int fd : _logFd) {
            if (id == "")
                write(fd, (dateAff + " : " + log + "\n").c_str(), dateAff.size() + log.size() + 4);
            else
                write(fd, (dateAff + " : " + id + " -> " + log + "\n").c_str(), dateAff.size() + log.size() + id.size() + 8);
        }
    }

};

#endif //SRV_FIRE_LOGER_HPP
