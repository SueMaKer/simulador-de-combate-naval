#pragma once

#include "Ship.hpp"


class SplayTreeNode {
public:
    int key;
    SplayTreeNode *left, *right;

    SplayTreeNode(int val);
};

class Splay : public Ship {
private:
    SplayTreeNode* root;

    void deleteTree(SplayTreeNode* node);
    void setSet();
    void populateTree();
    SplayTreeNode* insert(SplayTreeNode* node, int key);
    SplayTreeNode* rightRotate(SplayTreeNode* x);
    SplayTreeNode* leftRotate(SplayTreeNode* x);
    SplayTreeNode* splay(SplayTreeNode* root, int key);

public:
    Splay();
    ~Splay();
    int search(int key);
    int getPower() override;
    void printReport();
};