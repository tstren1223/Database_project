#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>
#include "Otherserving.h"

using namespace std;


class Package : public OtherServing
{
private:
    double packageLength;
    double packageWidth;
    double packageHeight;
    double packageWeight;
    string startLocation;
    string endLocation;
    int packageCost;
public:
    Package();
    void setLength(double length);
    void setWidth(double width);
    void setHeight(double height);
    void setWeight(double weight);
    void setStart(string location);
    void setEnd(string location);
    void setCost();
    double getLength();
    double getWidth();
    double getHeight();
    double getWeight();
    string getStart();
    string getEnd();
    int getCost();
    int computeCost();
    bool operator==(Package p);

};

#endif // PACKAGE_H
