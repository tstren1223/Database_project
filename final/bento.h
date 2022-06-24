#ifndef BENTO_H
#define BENTO_H


#include "otherserving.h"
#include <string>
#include <QTime>

using namespace std;


class Bento : public OtherServing
{
private:
    /*
   string bentoType;
   int bentoCost;
   QTime arriveClock;
   */
    string bentoMeat;
    string bentoVegatable;
    //type and number

public:
    Bento();
    void setMeat(string type);
    //void setCost(int cost);
    //void setTime(QTime t);
    string getMeat();
    void setVeg(string veg);
    string getVeg();
    //int getCost();
    //QTime getClock();
    bool operator==(Bento b);
};

#endif // BENTO_H
