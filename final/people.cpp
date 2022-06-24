#include "people.h"
People::People(){
    account="";
    password="";
}
People::People(string acc,string pass){
    account=acc;
    password=pass;
}
bool People::accountVerify(string acc, string pass){
    if(acc==account&&pass==password)
        return true;
    return false;
}
void People::setNewPassword(string new_pass){
    password=new_pass;
}
string People::getAccount(){
    return account;
}
string People::getPassword(){
    return password;
}
