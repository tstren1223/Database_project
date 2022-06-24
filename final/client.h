#ifndef CLIENT_H
#define CLIENT_H

#include "people.h"
#include "tickets.h"
#include <vector>
using namespace std;

class Client : public People
{
private:
    unsigned int clientID;
    vector <Ticket> tickets;
public:
    Client();
    Client(string,string);
    int money;
    string clientName;
    vector<Ticket>* gettickets();
    void setClientID(unsigned int id);
    unsigned int getClientID();
    bool buyTickets(vector <Ticket> new_ticket);
    bool modifyTickets(vector <Ticket> old_tickets, vector <Ticket> new_tickets);
    bool cancelTickets(vector <Ticket> tickets);
    bool operator==(Client);


};

#endif // CLIENT_H
