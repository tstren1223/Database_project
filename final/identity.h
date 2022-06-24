#ifndef IDENTITY_H
#define IDENTITY_H

#include <string>
#include "otherserving.h"

using namespace std;

class Identity : public OtherServing
{
private:
    string identity;
    bool specialServing;
public:
    Identity();
    void setIdentity(string iden);
    void setSpecialServing(bool need);
    string getIdentity();
    bool getSpecialServing();
};

#endif // IDENTITY_H
