
#ifndef __CLIENT_HH__
#define __CLIENT_HH__

#include <stack>

#include "NetworkTypes.hh"

class Client
{
public:
    Client();
    ~Client();

    void                        setId(__client_id id);
    void                        setSock(__socket socket);
    void                        setSin(const __sockaddr_in &sin);
    void                        setSinSize(__sockaddr_in_size sinSize);
    void                        pushData(const __packet_data &data);

    __client_id                 getId() const;
    __socket                    getSock() const;
    const __sockaddr_in         &getSin() const;
    __sockaddr_in_size          getSinSize() const;

private:
    __client_id                 m_id;
    __socket                    m_sock;
    __sockaddr_in               m_sin;
    __sockaddr_in_size          m_sinSize;
    std::stack<__packet_data>   m_dataStack;
};

#endif /* !__CLIENT_HH__ */