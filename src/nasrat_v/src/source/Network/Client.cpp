
#include "../../header/Network/Client.hh"

Client::Client() = default;

Client::~Client() = default;

void Client::setId(__client_id id)
{
    m_id = id;
}

void Client::setSock(__socket socket)
{
    m_sock = socket;
}

void Client::setSin(const __sockaddr_in &sin)
{
    m_sin = sin;
}

void Client::setSinSize(__sockaddr_in_size sinSize)
{
    m_sinSize = sinSize;
}

void Client::pushData(const __packet_data &data)
{
    m_dataVector.push_back(data);
}

void Client::resetData()
{
    m_dataVector.clear();
}

__client_id Client::getId() const
{
    return (m_id);
}

__socket Client::getSock() const
{
    return (m_sock);
}

const __sockaddr_in &Client::getSin() const
{
    return (m_sin);
}

__sockaddr_in_size Client::getSinSize() const
{
    return (m_sinSize);
}

const __data_vector &Client::getData() const
{
    return (m_dataVector);
}

bool Client::isData() const
{
    return (!m_dataVector.empty());
}