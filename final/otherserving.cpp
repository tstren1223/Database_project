#include "otherserving.h"

OtherServing::OtherServing()
{
    bento=false;
    package=false;
    servingCost=0;
}

void OtherServing::setBento(bool serve)
{
    bento=serve;
}

void OtherServing::setPackage(bool serve)
{
    package=serve;
}

void OtherServing::setServingCost(int money)
{
    servingCost=money;
}

bool OtherServing::getBento()
{
    return bento;
}

bool OtherServing::getPackage()
{
    return package;
}

int OtherServing::getServingCost()
{
    return servingCost;
}

bool OtherServing::operator==(OtherServing o)
{
    //only compare bool
    //if need to compare the detail, need to call the operator== in bento and package class
    if(bento!=o.bento){
        return false;
    }
    if(package!=o.package){
        return false;
    }
    if(servingCost!=o.servingCost){
        return false;
    }
    return true;
}

