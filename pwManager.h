#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

class Account{
    private:
        string accountName;
        string username;
        string password;
    public:
        Account();
        Account(string accountName, string username, string password);
        ~Account();
        void displayInfo();
        string getAccount();
        string getUsername();
        string getPassword();
        void setAccount(string accountName);
        void setUsername(string username);
        void setPassword(string password);
};

void menuOption(string fileName);
bool verifyFile(string fileName);
void initalize(vector<Account>& accountList,string fileName);
Account addAcc();
void editAcc(vector<Account>& account);
void removeAcc(vector<Account>& accountList);
bool mySort(Account a, Account b);
void searchFile(vector<Account>& accountList,string search);
void writeToFile(vector<Account>& v, string fileName);
