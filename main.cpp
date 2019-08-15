//
//  main.cpp
//  srv-fire
//
//  Created by Alexandre Bouvier on 12/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#include "network/include/connectionHandler.h"
#include <unistd.h>

int main(int ac, char **av, char **env){
    int     pid;
    connectionHandler manager;

    srand(time(NULL));
/*    if ((pid = fork()) == -1)
        return 1;
    if (pid == 0)
        return execve("upload.sh",  av, env);
    else { */
        if (!manager.initConnection() /*|| !manager.initUDPConnection() */)
            return 1;
        manager.start(env);
//    }
    return 0;
}
