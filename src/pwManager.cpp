#include"pwManager.h"

pwManager::pwManager(){
    this->accountList = new AccountTree(); 
    this->fileName = "password.txt";
    fileParser.setMainFile(fileName);
}

// Loads relevent data into the AccountTree class
void pwManager::init(){
    if(verifyFile()){
        string data = fileParser.parseFile();
        stringstream ss(data);
        while(ss >> data){
            Account* tempAcc = new Account();
            tempAcc->setAccountName(data);
            ss >> data;
            tempAcc->setAccountUser(data);
            ss >> data;
            tempAcc->setAccountPassword(data);
            accountList->insert(tempAcc);
        }
    }
    menuOption();
}

bool pwManager::verifyFile(){
    fstream myFile(this->fileName);
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
        ofstream myFile(this->fileName);
        myFile.close();
    }
    return false;
}

void pwManager::menuOption(){
    string input;
    do{
        cout << "[1]Add [2]Edit [3]Remove\n";
        cout << "Search account: ";
        cin >> input;
        cout << "-----------------------------------------------------------------------\n";
        if(input == "1"){
            cout << "Adding...\n";
            accountList->insert(addAcc());
            cout << "-----------------------------------------------------------------------\n";
        }else if(input == "2"){
            cout << "Editing...\n";
            editAcc();
            cout << "-----------------------------------------------------------------------\n";
        }else if(input == "3"){
            cout << "Removing...\n";
            removeAcc();
            cout << "-----------------------------------------------------------------------\n";
        }else if(input == "ALL"){
            cout << "\n";
            accountList->inOrder();
            cout << "-----------------------------------------------------------------------\n";
        }else if(input == "BACKUP"){
            cout << "File backedup...\n";
            //to be implemented
            cout << "-----------------------------------------------------------------------\n";
        }else if(input != "END"){
            cout << "Results:\n";
            queue<Account*> accounts = accountList->searchtree(input);
            while(!accounts.empty()){
                cout << accounts.front()->display();
                accounts.pop();
            }
            cout << "-----------------------------------------------------------------------\n";
        }
    }while(input != "END");
}

Account* pwManager::addAcc(){
    string accountName;
    string username;
    string password;
    cout << "Enter account name: ";
    cin >> accountName;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    Account* tempAccount = new Account(accountName,username,password);
    fileParser.writeData(accountName,username,password);
    return tempAccount;
}

void pwManager::removeAcc(){
    bool accountFound = false;
    string input;
    cout << "Account name: ";
    cin >> input;
    if(accountList->remove(input)){
        cout << "Removed\n";
        fileParser.removeData(input);
    }else{
        cout << "Failed to find account to remove\n";
    }
}

void pwManager::editAcc(){
    bool accountFound = false;
    string input;
    cout << "Account name: ";
    cin >> input;
    if(accountList->edit(input)){
        Account* temp = accountList->searchtree(input).front();
        fileParser.editData(input,temp->getAccountName(),temp->getAccountUser(),temp->getAccountPassword());
        delete temp;
    }
}


