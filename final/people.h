//main purpose::be inherited
#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>
using namespace std;

class People{
private:
    string account;
    string password;
public:
    People();
    People(string acc,string pass);
    bool accountVerify(string acc,string pass);//for log in part
    void setNewPassword(string new_pass);//for legal accout
    string getAccount();
    string getPassword();
};

#endif // PEOPLE_H
