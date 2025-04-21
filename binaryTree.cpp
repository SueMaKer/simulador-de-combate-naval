#include "BinaryTree.hpp"

using namespace std;
using namespace std::chrono;

// --- BTNode constructor ---
BinaryTree::BTNode::BTNode(int val) : key(val), left(nullptr), right(nullptr) {}

// --- Constructor ---
BinaryTree::BinaryTree()
    : Ship("BinaryTree", 4, 150, 100, 500, 'B'),
      root(nullptr) {
    setSet();
    populateTree();
}

// --- Destructor ---
BinaryTree::~BinaryTree() {
    deleteTree(root);
}

// --- Populate Set with Random Values ---
void BinaryTree::setSet() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
        set.insert(val);
    }
}

// --- Insert all elements into the tree ---
void BinaryTree::populateTree() {
    for (int i = 0; i < set.getSize(); ++i) {
        insert(set.getElement(i));
    }
}

// --- Delete entire tree ---
void BinaryTree::deleteTree(BTNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// --- Insert wrapper ---
void BinaryTree::insert(int key) {
    root = insertRec(root, key);
}

// --- Insert recursive ---
BinaryTree::BTNode* BinaryTree::insertRec(BTNode* node, int key) {
    if (!node) return new BTNode(key);
    if (key < node->key)
        node->left = insertRec(node->left, key);
    else if (key > node->key)
        node->right = insertRec(node->right, key);
    return node;
}

// --- Search with iteration count and timing ---
int BinaryTree::search(int key) {
    lastIterations = 0;
    foundLastValue = false;

    auto start = high_resolution_clock::now();
    BTNode* current = root;

    while (current != nullptr) {
        ++lastIterations;
        if (key == current->key) {
            foundLastValue = true;
            break;
        } else if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    auto stop = high_resolution_clock::now();
    lastSearchTime = duration<double, std::milli>(stop - start).count();

    return lastIterations;
}

// --- getPower based on search ---
int BinaryTree::getPower() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int target = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
    int iterations = search(target);
    return iterations > 0 ? DAMAGE_CONSTANT / iterations : 0;
}
