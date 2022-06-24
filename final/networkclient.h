#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "staff.h"
#include"client.h"
#include <QSqlResult>
#include <QSqlDatabase>
#include <QSqlQuery>
class NetworkClient
{
private:
    vector <Client> clientList;
    vector <Staff> staffList;
    string connectToIP;
    unsigned short connectToPort;

public:
    NetworkClient();
    void newTicket(vector <Ticket> ticket, Client client);
    vector <Ticket> searchTickets(vector <Ticket> ticket);
    void modifyTickets(vector <Ticket> new_ticket, vector <Ticket> old_ticket,Client client);
    void cancelTickets(vector <Ticket> cancel_ticket ,Client client);
    void newClient(Client client,QSqlQuery *query);
    bool login(Client,int &,Client*&,QSqlQuery *query);
    bool exist(Client,QSqlQuery *query);
    void requestToServer(bool havingClient);
};

#endif // NETWORKCLIENT_H
