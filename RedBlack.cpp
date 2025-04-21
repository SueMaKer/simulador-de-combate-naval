#include "RedBlack.hpp"

// Constructor for RedBlack ship
RedBlack::RedBlack() : Ship("RedBlack", 6, 220, 130, 720, 'R'), root(nullptr) {
    setSet();          // Generate a set of random values
    populateTree();    // Insert values into the Red-Black Tree
}

// Destructor - deletes all nodes in the tree
RedBlack::~RedBlack() {
    deleteTree(root);
}

// Generates a set of unique random integers
void RedBlack::setSet() {
    srand(static_cast<unsigned int>(time(nullptr)));  // Initialize random seed
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
        set.insert(val);
    }
}

// Inserts all elements from the set into the Red-Black Tree
void RedBlack::populateTree() {
    for (int i = 0; i < set.getSize(); ++i) {
        insert(set.getElement(i));
    }
}

// Recursively deletes all nodes from the tree
void RedBlack::deleteTree(RBNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Public method to insert a value into the Red-Black Tree
void RedBlack::insert(int key) {
    RBNode* node = new RBNode(key);
    root = bstInsert(root, node);  // Standard BST insert
    fixViolation(node);            // Fix Red-Black Tree properties
}

// BST-style insertion used by the Red-Black Tree
RBNode* RedBlack::bstInsert(RBNode* root, RBNode* node) {
    if (!root) return node;

    if (node->key < root->key) {
        root->left = bstInsert(root->left, node);
        root->left->parent = root;
    } else if (node->key > root->key) {
        root->right = bstInsert(root->right, node);
        root->right->parent = root;
    }
    return root;
}

// Performs a left rotation around node x
void RedBlack::rotateLeft(RBNode*& root, RBNode*& x) {
    RBNode* y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Performs a right rotation around node y
void RedBlack::rotateRight(RBNode*& root, RBNode*& y) {
    RBNode* x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;

    if (!y->parent)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fixes Red-Black Tree property violations after insertion
void RedBlack::fixViolation(RBNode*& node) {
    RBNode* parent = nullptr;
    RBNode* grandparent = nullptr;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent = node->parent;
        grandparent = parent->parent;

        // Case: Parent is left child of grandparent
        if (parent == grandparent->left) {
            RBNode* uncle = grandparent->right;

            // Case 1: Uncle is RED
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                // Case 2: Node is right child
                if (node == parent->right) {
                    rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }

                // Case 3: Node is left child
                rotateRight(root, grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            // Case: Parent is right child of grandparent
            RBNode* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(root, parent);
                    node = parent;
                    parent = node->parent;
                }

                rotateLeft(root, grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    root->color = BLACK;  // Root must always be black
}

// Searches for a value in the tree, records search time and steps
int RedBlack::search(int key) {
    lastIterations = 0;
    foundLastValue = false;

    auto start = high_resolution_clock::now();
    RBNode* current = root;

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

// Calculates ship's power based on how efficient the search is
int RedBlack::getPower() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int target = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
    int iterations = search(target); 
    return iterations > 0 ? DAMAGE_CONSTANT / iterations : 0;
}