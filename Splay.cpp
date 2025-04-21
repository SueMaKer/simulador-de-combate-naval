#include "Splay.hpp"

using namespace std;
using namespace std::chrono;

SplayTreeNode::SplayTreeNode(int val) : key(val), left(nullptr), right(nullptr) {}

Splay::Splay() : Ship("Splay", 5, 200, 120, 700, 'S'), root(nullptr){
    setSet();
    populateTree();
}

Splay::~Splay() {
    deleteTree(root);
}

void Splay::deleteTree(SplayTreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void Splay::setSet() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
        set.insert(val);
    }
}

void Splay::populateTree() {
    for (int i = 0; i < set.getSize(); ++i) {
        root = insert(root, set.getElement(i));
    }
}

SplayTreeNode* Splay::insert(SplayTreeNode* node, int key) {
    if (!node) return new SplayTreeNode(key);
    node = splay(node, key);

    if (node->key == key) return node;

    SplayTreeNode* newNode = new SplayTreeNode(key);
    if (key < node->key) {
        newNode->right = node;
        newNode->left = node->left;
        node->left = nullptr;
    } else {
        newNode->left = node;
        newNode->right = node->right;
        node->right = nullptr;
    }
    return newNode;
}

int Splay::search(int key) {
    lastIterations = 0;
    foundLastValue = false;

    auto start = high_resolution_clock::now();
    root = splay(root, key);
    auto stop = high_resolution_clock::now();

    lastSearchTime = duration<double, std::milli>(stop - start).count();
    foundLastValue = (root && root->key == key);
    return lastIterations;
}

int Splay::getPower() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int target = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
    int iterations = search(target);
    return iterations > 0 ? DAMAGE_CONSTANT / iterations : 0;
}


SplayTreeNode* Splay::rightRotate(SplayTreeNode* x) {
    ++lastIterations;
    SplayTreeNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayTreeNode* Splay::leftRotate(SplayTreeNode* x) {
    ++lastIterations;
    SplayTreeNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayTreeNode* Splay::splay(SplayTreeNode* root, int key) {
    if (!root || root->key == key) return root;

    ++lastIterations;

    if (key < root->key) {
        if (!root->left) return root;

        ++lastIterations;
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        } else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }

        return (root->left == nullptr) ? root : rightRotate(root);
    } else {
        if (!root->right) return root;

        ++lastIterations;
        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        } else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }

        return (root->right == nullptr) ? root : leftRotate(root);
    }
}