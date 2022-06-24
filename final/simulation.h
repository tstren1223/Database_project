#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <QDebug>
#include <QSqlResult>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "table.h"


using namespace std;

class Simulation
{
private:
    vector <Train> timeTable;
    QSqlQuery *query;
    QTime now;
    int stringToInt(string s);

public:
    Simulation();
    ~Simulation();
    //the aim of destructor is to update timeNow to database
    //so that we don't need to simulate at the begining
    void simul(QSqlQuery *query);
    //the main simulation function
    void setQuery(QSqlQuery *q);
    void setTrain(Train t);
    void setNow(QTime t);
    QTime getNow();
    void changeStop(QSqlQuery *query,string number,int i);
    void QTimeToInt(QTime t,int &h,int &m,int &s);
    void addDelay(QTime &t,int delay);
    vector <Train> getTimeTable();
    void initialize();
};

#endif // SIMULATION_H
