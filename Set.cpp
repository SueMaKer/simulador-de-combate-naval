#include "Set.hpp"

// Constructor: Initializes an empty set
Set::Set() : root(nullptr) {}

// Destructor: Frees memory by clearing the entire tree
Set::~Set() {
    clear(root);
}

// Recursive helper to insert a value into the tree
Set::Node* Set::insert(Node* node, int value) {
    if (!node) return new Node(value);
    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    return node;
}

// Recursive helper to search for a value in the tree
bool Set::search(Node* node, int value) const {
    if (!node) return false;
    if (value == node->value) return true;
    if (value < node->value)
        return search(node->left, value);
    else
        return search(node->right, value);
}

// Finds the minimum node (left-most node) in the subtree
Set::Node* Set::findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Recursive helper to remove a value from the tree
Set::Node* Set::remove(Node* node, int value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = remove(node->left, value);
    } else if (value > node->value) {
        node->right = remove(node->right, value);
    } else {
        // Node with no children
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        // Node with only right child
        else if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        // Node with only left child
        else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // Node with two children: find in-order successor
        else {
            Node* temp = findMin(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }
    }
    return node;
}

// Recursive in-order traversal to print tree values
void Set::display(Node* node) const {
    if (!node) return;
    display(node->left);
    std::cout << node->value << " ";
    display(node->right);
}

// Recursive helper to delete all nodes in the tree
void Set::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// Recursive helper to compute total number of nodes in the tree
int Set::getSize(Node* node) const {
    if (!node) return 0;
    return 1 + getSize(node->left) + getSize(node->right);
}

// Recursive helper to get an element by index (in-order)
bool Set::getElementAt(Node* node, int& counter, int index, int& result) const {
    if (!node) return false;

    if (getElementAt(node->left, counter, index, result)) return true;

    if (counter == index) {
        result = node->value;
        return true;
    }
    counter++;

    return getElementAt(node->right, counter, index, result);
}

// Public method to insert a value into the set
void Set::insert(int value) {
    if (!search(value)) {
        root = insert(root, value);
        std::cout << value << " inserted.\n";
    } else {
        std::cout << value << " already exists.\n";
    }
}

// Public method to search for a value in the set
bool Set::search(int value) const {
    return search(root, value);
}

// Public method to remove a value from the set
void Set::remove(int value) {
    if (search(value)) {
        root = remove(root, value);
        std::cout << value << " removed.\n";
    } else {
        std::cout << value << " not found.\n";
    }
}

// Public method to display all values in the set (in-order)
void Set::display() const {
    std::cout << "Set contents: ";
    display(root);
    std::cout << "\n";
}

// Public method to get the number of elements in the set
int Set::getSize() const {
    return getSize(root);
}

// Public method to get the value at a given index (0-based, in-order)
int Set::getElement(int index) const {
    int size = getSize();
    if (index < 0 || index >= size) {
        std::cerr << "Index out of bounds\n";
        return -1; 
    }

    int counter = 0;
    int result = -1;
    getElementAt(root, counter, index, result);
    return result;
}