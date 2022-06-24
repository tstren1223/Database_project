#include "train.h"

Train::Train()
{
    type="";
    trainNumber=-1;
    passThrough="";
    currentLocation="";
    nextStop="";
    arrivalTime.setHMS(0,0,0);
    realArrivalTime.setHMS(0,0,0);
    full=false;
    carriageNumber=4;
    carriagePeople.resize(carriageNumber);
    delayTime=0;
}

void Train::setType(string t)
{
    type=t;
}

void Train::setTrainNumber(int number)
{
    trainNumber=number;
}

void Train::setPassThrough(string pass)
{
    passThrough=pass;
}

void Train::setCurrentLocation(string location)
{
    currentLocation=location;
}

void Train::setNextStop(string location)
{
    nextStop=location;
}

void Train::setArrivalTime(QTime t)
{
    arrivalTime=t;
}

void Train::setRealArrivalTime(QTime t)
{
    realArrivalTime=t;
}

void Train::setCarriageNumber(int c)
{
    carriageNumber=c;
}

void Train::setCarriagePeople(int carriage, int number)
{
    carriagePeople[carriage]+=number;
}


void Train::setDelayTime(int d)
{
    delayTime=d;
}

void Train::setMoving(bool move)
{
    moving=move;
}

void Train::setTerminal(bool s)
{
    terminal=s;
}

void Train::setStationNumber(int s)
{
    stationNumber=s;
}

void Train::setPassStation(int s)
{
    passStation=s;
}

string Train::getType()
{
    return type;
}

string Train::getPass()
{
    return passThrough;
}

int Train::getTrainNumber()
{
    return trainNumber;
}

string Train::getCurrentLocation()
{
    return currentLocation;
}

string Train::getNextStop()
{
    return nextStop;
}

QTime Train::getArrivalTime()
{
    return arrivalTime;
}

QTime Train::getRealArrivalTime()
{
    return realArrivalTime;
}

int Train::getCarriageNumber()
{
    return carriageNumber;
}

vector<int> Train::getCarriagePeople()
{
    return carriagePeople;
}

int Train::getDelayTime()
{
    return delayTime;
}

bool Train::getMoving()
{
    return moving;
}

bool Train::getTerminal()
{
    return terminal;
}

int Train::getStationNumber()
{
    return stationNumber;
}

int Train::getPassStation()
{
    return passStation;
}

