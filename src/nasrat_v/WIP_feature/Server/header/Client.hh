
#ifndef __CLIENT_HH__
#define __CLIENT_HH__

#include <vector>

#include "NetworkTypes.hh"

typedef std::vector<__packet_data> __data_vector;

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
    void                        resetData();

    __client_id                 getId() const;
    __socket                    getSock() const;
    const __sockaddr_in         &getSin() const;
    __sockaddr_in_size          getSinSize() const;
    const __data_vector         &getData() const;
    bool                        isData();

private:
    __client_id                 m_id;
    __socket                    m_sock;
    __sockaddr_in               m_sin;
    __sockaddr_in_size          m_sinSize;
    __data_vector               m_dataVector;
};

#endif /* !__CLIENT_HH__ */