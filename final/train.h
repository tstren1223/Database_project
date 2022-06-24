//under simulation system
#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <QTime>
#include <vector>
using namespace std;
class Train
{
private:
    string type;
    int trainNumber;
    string passThrough;
    string currentLocation;
    string nextStop;
    QTime arrivalTime;
    QTime realArrivalTime;
    bool full;
    int carriageNumber;
    vector <int> carriagePeople;
    int delayTime;
    bool moving;
    //whether the train is moving
    bool terminal;
    //whether the train is going to the terminal station
    int stationNumber;
    int passStation;
public:
    Train();
    void setType(string t);
    void setTrainNumber(int number);
    void setPassThrough(string pass);
    void setCurrentLocation(string location);
    void setNextStop(string location);
    void setArrivalTime(QTime t);
    void setRealArrivalTime(QTime t);
    void setCarriageNumber(int c);
    void setCarriagePeople(int carriage,int number);
    void setDelayTime(int d);
    void setMoving(bool move);
    void setTerminal(bool s);
    void setStationNumber(int s);
    void setPassStation(int s);
    string getType();
    string getPass();
    int getTrainNumber();
    string getCurrentLocation();
    string getNextStop();
    QTime getArrivalTime();
    QTime getRealArrivalTime();
    int getCarriageNumber();
    vector <int> getCarriagePeople();
    int getDelayTime();
    bool getMoving();
    bool getTerminal();
    int getStationNumber();
    int getPassStation();
};

#endif // TRAIN_H
