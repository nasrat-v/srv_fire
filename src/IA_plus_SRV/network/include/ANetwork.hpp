//
//  ANetwork.h
//  srv-fire
//
//  Created by Alexandre Bouvier on 13/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#ifndef ANetwork_h
#define ANetwork_h

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include "../../Utilitary/header/json.hpp"


class ANetwork {
protected:
    int     _cameraSocket;
    int     _embededSocket;
    int     _iaSocket;

protected:
    curlpp::Cleanup     RAII;
    std::string        _url;

public:
    ANetwork(const std::string &url)
    {
        _url = url;
    }

    virtual ~ANetwork() {}

    void    setEmbeded(int Socket){_embededSocket = Socket;}
    int     getEmbeded() const {return (_embededSocket);}

    void    setCamera(int Socket){_cameraSocket = Socket;}
    int     getCamera() const {return (_cameraSocket);}

    void    setIA(int Socket){_iaSocket = Socket;}
    int     getIA() const {return (_iaSocket);}
};

#endif /* ANetwork_h */
