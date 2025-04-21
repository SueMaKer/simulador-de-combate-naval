#include "Splay.hpp"

using namespace std;
using namespace std::chrono;

// Node structure for the Splay Tree
SplayTreeNode::SplayTreeNode(int val) : key(val), left(nullptr), right(nullptr) {}

// Constructor for the Splay ship
Splay::Splay() : Ship("Splay", 5, 200, 120, 700, 'S'), root(nullptr) {
    setSet();        // Generate a set of random values
    populateTree();  // Insert values into the splay tree
}

// Destructor to clean up memory
Splay::~Splay() {
    deleteTree(root);
}

// Recursively deletes all nodes in the tree
void Splay::deleteTree(SplayTreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Generates a custom set of unique random numbers
void Splay::setSet() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
        set.insert(val);  // Custom set class is assumed
    }
}

// Populates the splay tree using all values in the set
void Splay::populateTree() {
    for (int i = 0; i < set.getSize(); ++i) {
        root = insert(root, set.getElement(i));
    }
}

// Inserts a value into the splay tree
SplayTreeNode* Splay::insert(SplayTreeNode* node, int key) {
    if (!node) return new SplayTreeNode(key);

    node = splay(node, key); // Splay the node to the root

    if (node->key == key) return node; // Key already exists

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

// Searches for a key and measures performance
int Splay::search(int key) {
    lastIterations = 0;
    foundLastValue = false;

    auto start = high_resolution_clock::now();
    root = splay(root, key);  // Move key to root if found
    auto stop = high_resolution_clock::now();

    lastSearchTime = duration<double, std::milli>(stop - start).count();
    foundLastValue = (root && root->key == key);  // Was the value found?
    return lastIterations;
}

// Calculates the ship's power based on search performance
int Splay::getPower() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int target = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
    int iterations = search(target);
    return iterations > 0 ? DAMAGE_CONSTANT / iterations : 0;
}

// Performs a right rotation
SplayTreeNode* Splay::rightRotate(SplayTreeNode* x) {
    ++lastIterations;
    SplayTreeNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Performs a left rotation
SplayTreeNode* Splay::leftRotate(SplayTreeNode* x) {
    ++lastIterations;
    SplayTreeNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Main splay operation: moves the key to the root
SplayTreeNode* Splay::splay(SplayTreeNode* root, int key) {
    if (!root || root->key == key) return root;

    ++lastIterations;

    // Key is in left subtree
    if (key < root->key) {
        if (!root->left) return root;

        ++lastIterations;

        // Zig-Zig (Left Left)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (Left Right)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }

        return (root->left == nullptr) ? root : rightRotate(root);
    }

    // Key is in right subtree
    else {
        if (!root->right) return root;

        ++lastIterations;

        // Zag-Zag (Right Right)
        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        // Zag-Zig (Right Left)
        else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left)
                root->right = rightRotate(root->right);
        }

        return (root->right == nullptr) ? root : leftRotate(root);
    }
}