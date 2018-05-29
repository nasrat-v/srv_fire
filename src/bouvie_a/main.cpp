//
//  main.cpp
//  srv-fire
//
//  Created by Alexandre Bouvier on 12/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#include <iostream>
#include "Include/ConnectionHandler.h"

int main(){
    ConnectionHandler manager;

    manager.start();
    return 0;
}
