#include "client.h"

Client::Client()
{
    clientID=-1;
}
Client::Client(string a,string p):People(a,p){

}
void Client::setClientID(unsigned int id)
{
    clientID=id;
}
bool Client::operator==(Client c){
    if(!c.accountVerify(getAccount(),getPassword()))
        return false;
   // if(getClientID()!=c.getClientID())
     //   return false;
    for(int i=0;i<(int)tickets.size();i++){
        if(!(tickets[i]==c.tickets[i]))
            return false;
    }
    return true;
}

unsigned int Client::getClientID()
{
    return clientID;
}

bool Client::buyTickets(vector<Ticket> new_tickets)
{
    for(int i=0;i<(int)new_tickets.size();i++){
        tickets.push_back(new_tickets[i]);
    }
    return true;
}

bool Client::modifyTickets(vector<Ticket> old_tickets, vector<Ticket> new_tickets)
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

    if(error)
        return false;
    return true;
}

bool Client::cancelTickets(vector<Ticket> old_tickets)
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
vector<Ticket>* Client::gettickets(){
    return &tickets;
}
