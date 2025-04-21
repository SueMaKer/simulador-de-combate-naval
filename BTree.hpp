#pragma once
#include "Ship.hpp"


const int BTREE_T = 3; 

class BTreeNode {
public:
    int* keys;
    int t;
    BTreeNode** children;
    int n;
    bool leaf;

    BTreeNode(int t, bool leaf);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    int search(int k, int& iterations);
    ~BTreeNode();
};

class BTree : public Ship {
private:
    BTreeNode* root;
    int t;

public:
    BTree();
    ~BTree();
    void insert(int k);
    int getPower() override;
    void printReport();
    int search(int k);
    void destroyTree(BTreeNode* node);
};