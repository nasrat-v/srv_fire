//
//  ANetwork.h
//  srv-fire
//
//  Created by Alexandre Bouvier on 13/03/2018.
//  Copyright © 2018 Alexandre Bouvier. All rights reserved.
//

#ifndef ANetwork_h
#define ANetwork_h

class ANetwork {
protected:
    int     _embededSocket;
    int     _graphicSocket;
public:
    ANetwork() {}
    ~ANetwork() {}
    void    setEmbeded(int Socket){_embededSocket = Socket;}
    void    setGraphic(int Socket){_graphicSocket = Socket;}
    int     getEmbeded() const {return (_embededSocket);}
    int     getGraphic() const {return (_graphicSocket);}
};

#endif /* ANetwork_h */
