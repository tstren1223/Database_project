#include "bento.h"

/*
Bento::Bento()
{
    bentoType="";
    bentoCost=0;
}
void Bento::setType(string type)
{
    bentoType=type;
}

void Bento::setCost(int cost)
{
    bentoCost=cost;
}

void Bento::setTime(QTime t)
{
    arriveClock=t;
}

string Bento::getType()
{
    return bentoType;
}

int Bento::getCost()
{
    return  bentoCost;;
}

QTime Bento::getClock()
{
    return arriveClock;
}

bool Bento::operator==(Bento b)
{
    if(bentoType!=b.bentoType){
        return false;
    }
    if(bentoCost!=b.bentoCost){
        return false;
    }
    if(arriveClock!=b.arriveClock){
        return false;
    }
    return true;
}
*/





Bento::Bento()
{
    bentoMeat="0";
    bentoVegatable="0";
    /*
    bentoType=new string[bentokind];
    bentonum=new int[bentokind];
    bentoCost=0;
    arriveClock.setHour(0);
    arriveClock.setMin(0);
    arriveClock.setSec(0);
    for(int i=0;i<bentokind;i++){
         bentoType[i]="";
         bentonum[i]=0;
    }
    bentoType[0]="Meat";
    bentoType[1]="Vegetable";
    */
}

void Bento::setMeat(string type)
{
    bentoMeat=type;
}

string Bento::getMeat()
{
    return bentoMeat;
}

void Bento::setVeg(string veg)
{
    bentoVegatable=veg;
}

string Bento::getVeg()
{
    return bentoVegatable;
}

/*
int Bento::getnum(int index){
    return bentonum[index];
}
void Bento::setnum(int num, int index){
    bentonum[index]=num;
}
void Bento::setType(string type,int index)
{
    bentoType[index]=type;
}

void Bento::setCost(int cost)
{
    bentoCost=cost;
}

void Bento::setTime(Clock t)
{
    arriveClock=t;
}

string Bento::getType(int index)
{
    return bentoType[index];
}

int Bento::getCost()
{
    return  bentoCost;;
}

Clock Bento::getClock()
{
    return arriveClock;
}
*/
bool Bento::operator==(Bento b)
{
    if(bentoMeat==b.getMeat() && bentoVegatable==b.getVeg()){
        return true;
    }
    return false;

    /*
    for(int i=0;i<bentokind;i++){
        if(bentoType[i]!=b.bentoType[i]){
            return false;
        }
    }
    if(bentoCost!=b.bentoCost){
        return false;
    }
    if(arriveClock.getHour()!=b.arriveClock.getHour()){
        return false;
    }
    return true;
    */
}






