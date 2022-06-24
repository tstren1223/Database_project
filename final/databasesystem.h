//data processing system
#ifndef DATABASESYSTEM_H
#define DATABASESYSTEM_H


#include <string>
#include <vector>
#include "simulation.h"
using namespace std;

class DatabaseSystem
{
private:
    string ipAddress;
    unsigned short portNumber;
public:
    DatabaseSystem();
    bool initializeDB();
    bool readfromDB(vector <Table>, vector <Train>);
    bool updateDB(vector <Table>, vector <Train>);
};
#endif // DATABASESYSTEM_H
