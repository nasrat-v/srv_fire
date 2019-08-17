//
// Created by nasrat_v on 5/20/19.
//

#ifndef OPENCV_SRV_IDMANAGER_HPP
#define OPENCV_SRV_IDMANAGER_HPP

#include <cstdio>

static size_t       _id_b = 0;

class IdManager
{
public:
    static size_t   newId() { return (_id_b++); }

private:
    IdManager() = default;
    ~IdManager() = default;
};

#endif //OPENCV_SRV_IDMANAGER_HPP
