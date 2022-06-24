#include "identity.h"

Identity::Identity()
{

}

void Identity::setIdentity(string iden)
{
    identity=iden;
}

void Identity::setSpecialServing(bool need)
{
    specialServing=need;
}

string Identity::getIdentity()
{
    return identity;
}

bool Identity::getSpecialServing()
{
    return specialServing;
}
