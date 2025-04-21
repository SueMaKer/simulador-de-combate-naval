#pragma once
#include <iostream>

class Set {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        Node(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        return node;
    }

    bool search(Node* node, int value) const {
        if (!node) return false;
        if (value == node->value) return true;
        if (value < node->value)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, int value) {
        if (!node) return nullptr;
        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* temp = findMin(node->right);
                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
        }
        return node;
    }

    void display(Node* node) const {
        if (!node) return;
        display(node->left);
        std::cout << node->value << " ";
        display(node->right);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    int getSize(Node* node) const {
        if (!node) return 0;
        return 1 + getSize(node->left) + getSize(node->right);
    }

    bool getElementAt(Node* node, int& counter, int index, int& result) const {
        if (!node) return false;

        if (getElementAt(node->left, counter, index, result)) return true;

        if (counter == index) {
            result = node->value;
            return true;
        }
        counter++;

        return getElementAt(node->right, counter, index, result);
    }

public:
    Set() : root(nullptr) {}
    ~Set() { clear(root); }

    void insert(int value) {
        if (!search(value)) {
            root = insert(root, value);
            std::cout << value << " inserted.\n";
        } else {
            std::cout << value << " already exists.\n";
        }
    }

    bool search(int value) const {
        return search(root, value);
    }

    void remove(int value) {
        if (search(value)) {
            root = remove(root, value);
            std::cout << value << " removed.\n";
        } else {
            std::cout << value << " not found.\n";
        }
    }

    void display() const {
        std::cout << "Set contents: ";
        display(root);
        std::cout << "\n";
    }

    int getSize() const {
        return getSize(root);
    }

    int getElement(int index) const {
        int size = getSize();
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds\n";
            return -1; // o lanza una excepción si preferís
        }

        int counter = 0;
        int result = -1;
        getElementAt(root, counter, index, result);
        return result;
    }
};