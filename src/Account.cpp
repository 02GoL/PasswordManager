#include"Account.h"

Account::Account(){};

Account::Account(string accountName,string username,string password){
    this->accountName = accountName;
    this->username = username;
    this->password = password;
}

string Account::getAccountName(){
    return accountName;
}

string Account::getAccountUser(){
    return username;
}

string Account::getAccountPassword(){
    return password;
}

void Account::setAccountName(string accountName){
    this->accountName = accountName;
}

void Account::setAccountUser(string username){
    this->username = username;
}

void Account::setAccountPassword(string password){
    this->password = password;
}

string Account::display(){
    return this->accountName + " | Username: " + this->username + " | Password: " + this->password + "\n"; 
}
