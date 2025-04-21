#pragma once
#include "Set.hpp"
#include "Ship.hpp"

class BinaryTree : public Ship {
public:
    BinaryTree();
    ~BinaryTree();

    int search(int key);
    int getPower() override;
    void printReport();

private:
    struct BTNode {
        int key;
        BTNode* left;
        BTNode* right;
        BTNode(int val);
    };

    BTNode* root;
    Set set;
    int lastIterations;
    double lastSearchTime;
    bool foundLastValue;

    void setSet();
    void populateTree();
    void deleteTree(BTNode* node);
    void insert(int key);
    BTNode* insertRec(BTNode* node, int key);
};