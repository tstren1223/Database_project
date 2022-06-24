#include "networkclient.h"

NetworkClient::NetworkClient(){
}
void NetworkClient::newTicket(vector<Ticket> ticket, Client client){
    for(int i=0;i<(int)clientList.size();i++){
        if(clientList[i]==client){
            clientList[i].buyTickets(ticket);
            break;
        }
    }
}
vector<Ticket> NetworkClient::searchTickets(vector<Ticket> ticket){

}

bool NetworkClient::login(Client c,int &si,Client* &a,QSqlQuery *query){
    string temp,temp2;
    temp=c.getAccount();
    temp2=c.getPassword();
    query->exec(("SELECT * FROM clientData WHERE account='"+temp+"' and keyword='"+temp2+"'").c_str());
    if(query->next()){
        a=new Client(c.getAccount(),c.getPassword());
        a->setClientID(query->value(0).toInt());
        a->clientName=a->getAccount()+QString::number(a->getClientID(),10).toStdString();
        return true;
    }
    si=2;
    return false;
    /*
    for(int i=0;i<(int)clientList.size();i++){
        if(clientList[i]==c){
            a=&clientList[i];
            return true;
        }
        else if((clientList[i].getAccount()==c.getAccount())){
                  si=1;
                  break;
        }
        else{
            si=2;
        }
    }
    return false;
*/
}
void NetworkClient::modifyTickets(vector<Ticket> new_ticket, vector<Ticket> old_ticket, Client client){
    for(int i=0;i<(int)clientList.size();i++){
        if(clientList[i]==client){
            clientList[i].modifyTickets(old_ticket,new_ticket);
            break;
        }
    }
}
bool NetworkClient::exist(Client client,QSqlQuery *query){
    query->exec(("SELECT * FROM clientData WHERE account='"+client.getAccount()+"'").c_str());
    if(query->next())
            return true;
    return false;
    /*
    for(int i=0;i<(int)clientList.size();i++){
        if(clientList[i].getAccount()==client.getAccount()){
            return true;
        }
    }
    return false;
*/
}
void NetworkClient::cancelTickets(vector<Ticket> cancel_ticket, Client client){
    for(int i=0;i<(int)clientList.size();i++){
        if(clientList[i]==client){
            clientList[i].cancelTickets(cancel_ticket);
            break;
        }
    }
}
void NetworkClient::newClient(Client client,QSqlQuery *query){
    string acc=client.getAccount();
    string pass=client.getPassword();
    string temp="('"+acc+"','"+pass+"')";
    string com="INSERT INTO clientData(account,keyword) VALUES "+temp;
    query->exec(QString::fromStdString(com));

    //clientList.push_back(client);
}
void NetworkClient::requestToServer(bool havingClient){
}
