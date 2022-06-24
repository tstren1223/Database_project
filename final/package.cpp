#include "package.h"

Package::Package()
{
    packageLength=0;
    packageWidth=0;
    packageHeight=0;
    packageWeight=0;
    startLocation="";
    endLocation="";
    packageCost=0;
}

void Package::setLength(double length)
{
    packageLength=length;
}

void Package::setWidth(double width)
{
    packageWidth=width;
}

void Package::setHeight(double height)
{
    packageHeight=height;
}

void Package::setWeight(double weight)
{
    packageWeight=weight;
}

void Package::setStart(string location)
{
    startLocation=location;
}

void Package::setEnd(string location)
{
    endLocation=location;
}

void Package::setCost()
{
    packageCost=computeCost();
}

double Package::getLength()
{
    return packageLength;
}

double Package::getWidth()
{
    return packageWeight;
}

double Package::getHeight()
{
    return packageHeight;
}

double Package::getWeight()
{
    return packageWeight;
}

string Package::getStart()
{
    return startLocation;
}

string Package::getEnd()
{
    return endLocation;
}

int Package::getCost()
{
    return packageCost;
}

int Package::computeCost()
{
    return ((getLength()*getHeight()*getWidth())*0.8*getWeight());
    //formula to calculate the cost
    //length*hwight*width*0.8*weight
}

bool Package::operator==(Package p)
{
    if(packageLength!=p.packageLength){
        return false;
    }
    if(packageHeight!=p.packageHeight){
        return false;
    }
    if(packageWidth!=p.packageWeight){
        return false;
    }
    if(packageWeight!=p.packageWeight){
        return false;
    }
    if(startLocation!=p.startLocation){
        return false;
    }
    if(endLocation!=p.endLocation){
        return false;
    }
    if(packageCost!=p.packageCost){
        return false;
    }
    return true;
}
