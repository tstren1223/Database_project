#include "staff.h"

Staff::Staff()
{
    staffID=-1;
}

void Staff::setStaffID(unsigned int id)
{
    staffID=id;
}

unsigned int Staff::getStaffID()
{
    return staffID;
}

bool Staff::getTickets(vector<Ticket> old_tickets)
{
    //check if all old ticket are in ticket
    bool error=false;
    int i,j;
    for(i=0;i<(int)old_tickets.size();i++){
        for(j=0;j<(int)tickets.size();j++){
            if(tickets[j]==old_tickets[i]){
                //find the tickets
                break;
            }
        }
        //if old ticket is not found, error occure
        error=true;
    }
    if(error)
        return false;
    return true;

}

bool Staff::modifyTickets(vector<Ticket> new_tickets, vector<Ticket> old_tickets)
{
    int i,j;
    int count=0;
    bool error=false;
    for(i=0;i<(int)old_tickets.size();i++){
        for(j=0;j<(int)tickets.size();j++){
            if(tickets[j]==old_tickets[i]){
                //find the old ticket is ticket
                tickets[i]=new_tickets[count];
                //modify it
                count++;
                break;
            }
        }
        error=true;
        //if old ticket is not found int ticket
        //error occure
    }
    if(count!=(int)new_tickets.size()){
        //put the remain ticket into ticket
        //if this is execute, that mean error is true
        for(i=count;i<(int)new_tickets.size();i++){
            tickets.push_back(new_tickets[i]);
        }
    }
    if(error)
        return false;
    return true;
}

bool Staff::cancelTickets(vector<Ticket> old_tickets)
{
    bool error=false;
    int i,j;
    for(i=0;i<(int)old_tickets.size();i++){
        for(j=0;j<(int)tickets.size();j++){
            if(tickets[j]==old_tickets[i]){
                //find the tickets to delete
                tickets.erase(tickets.begin()+j);
                break;
            }
        }
        //if old ticket is not found, error occure
        //cannot cancel the ticket
        error=true;
    }
    if(error)
        return false;
    return true;
}
