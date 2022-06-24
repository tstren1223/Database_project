#include "tickets.h"

Ticket::Ticket()
{

}

void Ticket::setTrainNumber(int number)
{
    trainNumber=number;
}

void Ticket::setTrainType(QString type)
{
    trainType=type;
}

void Ticket::setTrainDate(QDate d)
{
    trainDate=d;
}

void Ticket::setArriveTime(QTime t)
{
    arriveTime=t;
}

void Ticket::setStart(QString location)
{
    startStop=location;
}

void Ticket::setDest(QString location)
{
    destination=location;
}

void Ticket::setSeatNumber(double number)
{
    seatNumber=number;
}

void Ticket::setCarriageNumber(int number)
{
    carriageNumber=number;
}

void Ticket::setDiscount(double number)
{
    discount=number;
}

void Ticket::setCost(int money)
{
    cost=money;
}

void Ticket::setbento(Bento more)
{
    bento=more;
}



int Ticket::getTrainNumber()
{
    return trainNumber;
}

QString Ticket::getTrainType()
{
    return trainType;
}

QDate Ticket::getTrainDate()
{
    return trainDate;
}

QTime Ticket::getArrivalTime()
{
    return arriveTime;
}

QString Ticket::getStart()
{
    return startStop;
}

QString Ticket::getDest()
{
    return destination;
}

double Ticket::getSeatNumber()
{
    return seatNumber;
}

int Ticket::getCarriageNumber()
{
    return carriageNumber;
}

double Ticket::getDiscount()
{
    return discount;
}

int Ticket::getCost()
{
    return cost;
}

Bento Ticket::getBento()
{
    return bento;
}


void Ticket::setstartTime(QTime t){
    startTime=t;
}
bool Ticket::operator==(Ticket t)
{
    if(code!=t.code)
        return false;
    if(trainNumber!=t.trainNumber){
        return false;
    }
    if(trainType!=t.trainType){
        return false;
    }
    if(trainDate!=t.trainDate){
        return false;
    }
    if(arriveTime!=t.arriveTime)
        return false;
    if(startTime!=t.startTime)
        return false;
    if(startStop!=t.startStop){
        return false;
    }
    if(destination!=t.destination){
        return false;
    }
    if(seatNumber!=t.seatNumber){
        return false;
    }
    if(carriageNumber!=t.carriageNumber){
        return false;
    }
    if(discount!=t.discount){
        return false;
    }
    if(cost!=t.cost){
        return false;
    }
    if(!(bento==t.bento)){
        return false;
    }
    return true;
}

void Ticket::setCode(int number){
    code=number;
}
int Ticket::getCode(){
    return code;
}
QTime Ticket::getstartTime(){
    return startTime;
}


void Ticket::setSC(bool yn){
    specialcare=yn;
}

bool Ticket::getSC(){
    return specialcare;
}

void Ticket::setidentity(string a){
    identity=a;
}
string Ticket::getidentity(){
    return identity;
}





