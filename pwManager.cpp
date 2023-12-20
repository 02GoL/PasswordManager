#include"pwManager.h"

Account::Account():accountName("null"),username("null"),password("null"){}
Account::Account(string accountName, string username, string password):
    accountName(accountName),username(username),password(password){}
Account::~Account(){};
string Account::getAccount(){return accountName;}
string Account::getUsername(){return username;}
string Account::getPassword(){return password;}
void Account::setAccount(string accountName){this->accountName = accountName;}
void Account::setUsername(string username){this->username = username;}
void Account::setPassword(string password){this->password = password;}

void Account::displayInfo(){
    cout << accountName << " | ";
    if(this->username != "null"){
        cout << "Username: " << this->username << " | ";
    }
    if(this->password != "null"){
        cout << "Password: " + this->password + "\n";
    }
}

void menuOption(string fileName){
    vector<Account> accountList;
    string myFile = fileName;
    string input;
    if(verifyFile(myFile)){
        initalize(accountList,myFile);
    }
    do{
        cout << "[1]Add [2]Edit [3]Remove\n";
        cout << "Search account: ";
        cin >> input;
        cout << "-----------------------------------------------------------------------\n";
        if(input == "1"){
            cout << "Adding...\n";
            accountList.push_back(addAcc());
            sort(begin(accountList),end(accountList),mySort);
            cout << "-----------------------------------------------------------------------\n";
            writeToFile(accountList,myFile);
        }else if(input == "2"){
            cout << "Editing...\n";
            editAcc(accountList);
            writeToFile(accountList,myFile);
            cout << "-----------------------------------------------------------------------\n";
        }else if(input == "3"){
            cout << "Removing...\n";
            removeAcc(accountList);
            writeToFile(accountList,myFile);
            cout << "-----------------------------------------------------------------------\n";
        }else if(input == "ALL"){
            for(int i = 0; i < accountList.size(); i++){
                accountList[i].displayInfo();
            }
            cout << "-----------------------------------------------------------------------\n";
        }else if(input == "BACKUP"){
            cout << "File backedup...\n";
            writeToFile(accountList,"backUp"+myFile);
            cout << "-----------------------------------------------------------------------\n";
        }else{
            cout << "Results:\n";
            searchFile(accountList,input);
            cout << "-----------------------------------------------------------------------\n";
        }
    }while(input != "END");
}

bool verifyFile(string fileName){
    fstream myFile(fileName);
    if(myFile){
        myFile.close();
        cout << "-----------------------------------------------------------------------\n";
        cout << "File found...\n";
        cout << "Opening file...\n";
        cout << "-----------------------------------------------------------------------\n";
        return true;
    }else{
        myFile.close();
        cout << "-----------------------------------------------------------------------\n";
        cout << "File not found...\n";
        cout << "Creating file....\n";
        cout << "-----------------------------------------------------------------------\n";
        ofstream myFile(fileName);
        myFile.close();
    }
    return false;
}

//Reads file and stores it into the vector of Accounts
void initalize(vector<Account>& accountList,string fileName){
    ifstream file(fileName);
    Account acc;
    string data;
    int in;
    while(getline(file,data)){
        stringstream ss(data);
        in = 1;
        while(ss >> data){
            switch(in){
                case 1:
                    acc.setAccount(data);
                    break;
                case 2:
                    acc.setUsername(data);
                    break;
                case 3:
                    acc.setPassword(data);
                    break;
            }
            in++;
        }
        accountList.push_back(acc);
    }
    file.close();
}

Account addAcc(){
    Account acc;
    string input;
    cout << "Enter account name: ";
    cin >> input;
    acc.setAccount(input);
    cout << "Enter username: ";
    cin >> input;
    acc.setUsername(input);
    cout << "Enter password: ";
    cin >> input;
    acc.setPassword(input);
    return acc;
}

bool mySort(Account a, Account b){
    return a.getAccount() < b.getAccount();
}

void editAcc(vector<Account>& accountList){
    bool accountFound = false;
    string input;
    cout << "Account name: ";
    cin >> input;
    for(int i = 0; i < accountList.size(); i++){
        if(accountList[i].getAccount() == input){
            accountFound = true;
            cout << "Enter new account name: ";
            cin >> input;
            accountList[i].setAccount(input);
            cout << "Enter new username: ";
            cin >>  input;
            accountList[i].setUsername(input);
            cout << "Enter new password: ";
            cin >> input;
            accountList[i].setPassword(input);
            break;
        }
    }
    if(accountFound){
        cout << "Account has been edited\n";
    }else{
        cout << "Account not found\n";
    }
    
}

void removeAcc(vector<Account>& accountList){
    bool accountFound = false;
    string input;
    cout << "Account name: ";
    cin >> input;
    for(int i = 0; i < accountList.size(); i++){
        if(accountList[i].getAccount() == input){
            accountFound = true;
            cout << "'Confirm' | 'Cancel': ";
            cin >> input;
            if(input == "confirm" || input == "Confirm"){
                accountList.erase(accountList.begin()+i);
                cout << "Account has been removed\n";
            }else{
                cout << "Returning to menu\n";
                break;
            }
        }
    }
    if(!accountFound){
        cout << "Account not found\n";
    }
}

void searchFile(vector<Account>& accountList,string search){
    for(int i = 0; i < accountList.size(); i++){
        if(accountList[i].getAccount().find(search) == 0){
            accountList[i].displayInfo();
        }
    }
}

void writeToFile(vector<Account>& v, string fileName){
    ofstream myFile(fileName);
    myFile.clear();
    myFile.close();
    ofstream file(fileName, ios::app);
    for(int i = 0; i < v.size(); i++){
        file << v[i].getAccount() << " " << v[i].getUsername() << " " << v[i].getPassword() << "\n";
    }
    file.close();
}