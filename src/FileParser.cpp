#include"FileParser.h"

void FileParser::setMainFile(string fileName){
    this->fileName = fileName;
}

string FileParser::parseFile(){
    ifstream file(fileName);
    string data;
    string str;
    while(getline(file,data)){
        str+=data+" ";
    }
    file.close();
    return str;
}

void FileParser::writeData(string accountName, string username, string password){
    ofstream file;
    file.open(fileName,ios::app);
    file << accountName << " " << username << " " << password << "\n";
    file.close();
}

void FileParser::removeData(string accountName){
    ifstream inFile(fileName);
    string data;
    string name;
    string str;
    while(getline(inFile,data)){        
        stringstream ss(data);
        ss >> name;
        if(name == accountName){
            cout << "Changes made\n"; 
        }else{
            str+=data+"\n";
        }
    }
    inFile.close();
    ofstream outFile(fileName);
    outFile << str; 
    outFile.close();
}

void FileParser::editData(string oldAccountName,string accountName,string username,string password){
    removeData(oldAccountName);
    writeData(accountName,username,password);
}