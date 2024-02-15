#include<iostream>

using namespace std;

class Account{
    private:
        string accountName;
        string username;
        string password;
    public:
        Account();
        Account(string accountName, string username, string password);
        string getAccountName();
        string getAccountUser();
        string getAccountPassword();
        void setAccountName(string accountName);
        void setAccountUser(string username);
        void setAccountPassword(string password);
        string display();
};
