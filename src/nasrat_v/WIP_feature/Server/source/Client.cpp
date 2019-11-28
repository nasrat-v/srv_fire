
#include "../header/Client.hh"

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

void Client::pushData(const __client_data &data)
{
    std::cout << data << std::endl;
    m_dataStack.push(data);
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