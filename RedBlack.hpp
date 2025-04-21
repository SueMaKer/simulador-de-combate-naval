#pragma once
#include "Ship.hpp"

using namespace std;
using namespace std::chrono;

enum Color { RED, BLACK };

struct RBNode {
    int key;
    bool color;
    RBNode *left, *right, *parent;

    RBNode(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlack : public Ship {
private:
    RBNode* root;

public:
    RedBlack();
    ~RedBlack();

    void setSet();
    void populateTree();
    void deleteTree(RBNode* node);
    void insert(int key);
    RBNode* bstInsert(RBNode* root, RBNode* node);
    void rotateLeft(RBNode*& root, RBNode*& x);
    void rotateRight(RBNode*& root, RBNode*& y);
    void fixViolation(RBNode*& node);
    int search(int key);
    int getPower() override;
};