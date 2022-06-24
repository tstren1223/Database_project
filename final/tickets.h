#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <string>
#include "bento.h"
#include "package.h"
#include"QDate"
#include"QTime"
#include<time.h>
#include<stdlib.h>
using namespace std;

class Ticket
{
private:
    int code;
    int trainNumber;
    QString trainType;
    QDate trainDate;
    QTime arriveTime;
    QTime startTime;
    QString startStop;
    QString destination;
    double seatNumber;
    int carriageNumber;
    double discount;
    unsigned int cost;
    Bento bento;



    bool specialcare;
    string identity;

public:
    Ticket();
    void setCode(int number);
    int getCode();
    void setTrainNumber(int number);
    void setTrainType(QString type);
    void setTrainDate(QDate d);
    void setstartTime(QTime t);
    void setArriveTime(QTime t);
    void setStart(QString location);
    void setDest(QString location);
    void setSeatNumber(double number);
    void setCarriageNumber(int number);
    void setDiscount(double number);
    void setCost(int money);
    void setbento(Bento more);
    void setpackage(Package more);
    int getTrainNumber();
    QString getTrainType();
    QDate getTrainDate();
    QTime getstartTime();
    QTime getArrivalTime();
    QString getStart();
    QString getDest();
    double getSeatNumber();
    int getCarriageNumber();
    double getDiscount();
    int getCost();
    Bento getBento();
    Package getPackage();
    bool operator==(Ticket t);



    bool getSC();
    void setidentity(string a);
    string getidentity();
    void setSC(bool yn);//for special care




};

#endif // TICKET_H
