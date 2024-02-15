#include"FileParser.h"
#include"AccountTree.h"
using namespace std;

class pwManager{
    private:
        string fileName;
        AccountTree* accountList;
        FileParser fileParser;
    public:
        pwManager();
        void init();
        bool verifyFile();
        void menuOption();
        Account* addAcc();
        void removeAcc();
        void editAcc();
};







