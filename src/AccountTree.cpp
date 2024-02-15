#include"AccountTree.h"

Node::Node(Account* account){
    this->account = account;
    this->height = 1;
    this->right = NULL;
    this->left = NULL;
}

AccountTree::AccountTree(){
    root = NULL;
};

void AccountTree::insert(Account* newAccount){
    this->root = insert(newAccount,root);
}

Node* AccountTree::insert(Account* newAccount,Node* node){
    if(node == NULL){
        return new Node(newAccount);
    }
    if(node->account->getAccountName() < newAccount->getAccountName()){
        node->right = insert(newAccount,node->right);
    }else if(node->account->getAccountName() > newAccount->getAccountName()){
        node->left = insert(newAccount,node->left);
    }else{
        return node;
    }
    node->height = getMax(getHeight(node->right),getHeight(node->left))+1;
    int balanceFactor = getBalanceFactor(node);
    if(balanceFactor > 1){
        if(newAccount->getAccountName() < node->left->account->getAccountName()){
            return rotateRight(node);
        }else{
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if(balanceFactor < -1){
        if(newAccount->getAccountName() > node->right->account->getAccountName()){
            return rotateLeft(node);
        }else{
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}

queue<Account*> AccountTree::searchtree(string accountName){
    queue<Account*> list;
    searchtree(accountName,root,list);
    return list;
}

void AccountTree::searchtree(string accountName,Node* node, queue<Account*>& searchedAccounts){
    if(node == NULL){
        return;
    }
    if(accountName == node->account->getAccountName()){
        while(!searchedAccounts.empty()){
            searchedAccounts.pop();
        }
        searchedAccounts.push(node->account);

    }else if(node->account->getAccountName().find(accountName) != std::string::npos){
        searchedAccounts.push(node->account);
        searchtree(accountName,node->left,searchedAccounts);
        searchtree(accountName,node->right,searchedAccounts);

    }else if(accountName > node->account->getAccountName()){
        searchtree(accountName,node->right,searchedAccounts);

    }else if(accountName < node->account->getAccountName()){
        searchtree(accountName,node->left,searchedAccounts);

    }
}

bool AccountTree::remove(string accountName){
    queue<Account*> accounts = searchtree(accountName);
    if(accounts.size() == 1){
        string input;
        cout << "'Confirm' | 'Cancel': ";
        cin >> input;
        if(input == "confirm" || input == "Confirm"){
            root = remove(accountName, root);
            cout << "Account has been removed\n";
            return true;
        }else{
            cout << "Failed to remove, returning to menu\n";
            return false;
        }
    }else{
        return false;
    }
}

Node* AccountTree::remove(string accountName, Node* node){
    if(node == NULL){
        return node;
    }
    if(accountName > node->account->getAccountName()){
        node->right = remove(accountName, node->right);
    }else if(accountName < node->account->getAccountName()){
        node->left = remove(accountName, node->left);
    }else{
        if(node->left == NULL){
            return node->right;
        }else if(node->right == NULL){
            return node->left;
        }else{
            node->account = getMin(node);
            node->right = remove(node->account->getAccountName(), node->right);
        }
    }
    return node;
}

bool AccountTree::edit(string accountName){
    queue<Account*> list;
    searchtree(accountName,root,list);
    if(list.size() == 1){
        string input;
        cout << "Enter new account name: ";
        cin >> input;
        list.front()->setAccountName(input);
        cout << "Enter new username: ";
        cin >> input;
        list.front()->setAccountUser(input);
        cout << "Enter new password: ";
        cin >> input;
        list.front()->setAccountPassword(input);
        cout << "Changes have been made\n";
        return true;
    }else{
        cout << "Failed to find account\n";
        return false;
    }
}

// The functions below are helper functions for the AVL tree implemented
Node* AccountTree::rotateRight(Node* node){
    Node* newNode = node->left;
    node->left = newNode->right;
    newNode->right = node;
    node->height = getMax(getHeight(node->left),getHeight(node->right))+1;
    newNode->height = getMax(getHeight(node->left),getHeight(node->right))+1;
    return newNode;
}

Node* AccountTree::rotateLeft(Node* node){
    Node* newNode = node->right;
    node->right = newNode->left;
    newNode->left = node;
    node->height = getMax(getHeight(node->left),getHeight(node->right))+1;
    newNode->height = getMax(getHeight(node->left),getHeight(node->right))+1;
    return newNode;
}

int AccountTree::getBalanceFactor(Node* node){
    if(node == NULL){
        return 0;
    }else{
        return getHeight(node->left) - getHeight(node->right);
    }
}

int AccountTree::getHeight(Node* node){
    if(node == NULL){
        return 0;
    }else{
        return node->height;
    }
}

int AccountTree::getMax(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}

void AccountTree::inOrder(){
    inOrder(this->root);
}

void AccountTree::inOrder(Node* root){
    if(root == NULL){
        return;
    }else{
        inOrder(root->left);
        cout << root->account->display() << "\n";
        inOrder(root->right);
    }
}

Account* AccountTree::getMin(Node* node){
    while(node->left != NULL){
        node = node->left;
    }
    return node->account;
}