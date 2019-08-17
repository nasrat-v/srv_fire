//
//  main.cpp
//  srv-fire
//
//  Created by Alexandre Bouvier on 12/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#include "network/include/connectionHandler.h"

int main(int ac, char **av, char **env){
    connectionHandler manager;

    srand(time(NULL));
    if (!manager.initConnection() || !manager.initUDPConnection())
        return 1;
    manager.start(env);
    return 0;
}
