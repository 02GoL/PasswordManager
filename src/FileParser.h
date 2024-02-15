#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

class FileParser{
    private:   
        string fileName;
    public:
        void setMainFile(string fileName);
        string parseFile();
        void writeData(string accountName, string username, string password);
        void removeData(string accountName);
        void editData(string oldAccountName,string accountName,string username,string password);
};