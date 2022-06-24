//for showing tha data !
#ifndef TABLE_H
#define TABLE_H

#include "train.h"

#include <vector>
using namespace std;
class Table
{
private:
    string thisStation; //which station's table

    vector <Train> train;
public:
    Table();
    void setThisStation(string station);
    void setDelayTime(int min, int number);
    void setRecoverTime(int min , int number);    //min represent delay minutes
    string getThisStation();
    Train getTrainData(int Number);
};

#endif // TABLE_H
