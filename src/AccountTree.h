#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include"Account.h"

using namespace std;

class Node{
    public:
        Account* account;   
        int height;
        Node* left;
        Node* right;
        Node(Account* account);
};

class AccountTree{
    private:
        Node* root;
        Node* insert(Account* newAccount,Node* node);
        Node* remove(string accountName, Node* node);
        void searchtree(string accountName, Node* node, queue<Account*>& searchedAccounts);
        void inOrder(Node* root);
        Node* rotateRight(Node* node);
        Node* rotateLeft(Node* node);
        int getBalanceFactor(Node* node);
        int getHeight(Node* node);
        int getMax(int a, int b);
        Account* getMin(Node* node);
    public:
        AccountTree();
        void insert(Account* newAccount);
        void inOrder();
        queue<Account*> searchtree(string accountName);
        bool remove(string fileName);
        bool edit(string accountName);
};
