#ifndef OTHERSERVING_H
#define OTHERSERVING_H


class OtherServing
{
private:
    bool bento;
    bool package;
    int servingCost;
public:
    OtherServing();
    void setBento(bool serve);
    void setPackage(bool serve);
    void setServingCost(int money);
    bool getBento();
    bool getPackage();
    int getServingCost();
    bool operator==(OtherServing o);
};

#endif // OTHERSERVING_H
