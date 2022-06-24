#ifndef STAFF_H
#define STAFF_H


#include "people.h"
#include "tickets.h"
#include <vector>
using namespace std;
class Staff : public People
{
private:
    unsigned int staffID;
    vector <Ticket> tickets;
public:
    Staff();
    void setStaffID(unsigned int id);
    unsigned int getStaffID();
    bool getTickets(vector <Ticket> tickets);
    bool modifyTickets(vector <Ticket> new_tickets, vector <Ticket> old_tickets);
    bool cancelTickets(vector <Ticket> old_tickets);
};

#endif // STAFF_H
