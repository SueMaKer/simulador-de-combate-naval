#include "RedBlack.hpp"

RedBlack::RedBlack() : Ship("RedBlack", 6, 220, 130, 720, 'R'), root(nullptr) {
    setSet();
    populateTree();
}

RedBlack::~RedBlack() {
    deleteTree(root);
}

void RedBlack::setSet() {
    srand(static_cast<unsigned int>(time(nullptr)));  // Inicializar srand solo una vez
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
        set.insert(val);
    }
}

void RedBlack::populateTree() {
    for (int i = 0; i < set.getSize(); ++i) {
        insert(set.getElement(i));
    }
}

void RedBlack::deleteTree(RBNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void RedBlack::insert(int key) {
    RBNode* node = new RBNode(key);
    root = bstInsert(root, node);
    fixViolation(node);
}

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

void RedBlack::fixViolation(RBNode*& node) {
    RBNode* parent = nullptr;
    RBNode* grandparent = nullptr;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent = node->parent;
        grandparent = parent->parent;

        // Parent is left child of grandparent
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
        } else { // Parent is right child
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

    root->color = BLACK;
}

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

int RedBlack::getPower() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int target = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
    int iterations = search(target);
    return iterations > 0 ? DAMAGE_CONSTANT / iterations : 0;
}
