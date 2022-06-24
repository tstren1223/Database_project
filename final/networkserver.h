#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H


#include "client.h"
#include "staff.h"
#include <vector>
#include <string>
using namespace std;
class networkServer
{
private:
    vector <Client> clientList;
    vector <Staff> staffList;
    string ipAddress;
    unsigned short  portNumber;

public:
    networkServer();
    void newTicket(vector <Ticket> ticket, Client client);
    vector <Ticket> searchTickets(vector <Ticket> ticket);
    void modifyTickets(vector <Ticket> new_ticket,vector <Ticket> old_ticket, Client client);
    void cancelTickets(vector <Ticket> cancel_ticket,Client client);
    void newClient(Client client);
};

#endif // NETWORKSERVER_H
