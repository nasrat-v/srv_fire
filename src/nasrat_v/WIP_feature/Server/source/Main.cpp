
#include "../header/ProcessCommunication.hh"

int main()
{
    ProcessCommunication com;
    
    if (com.communicateWithServer() == NET_ERROR)
        return (1);
    return (0);
}