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

    // Helper for insert
    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        // If equal, do nothing (set stores unique values)
        return node;
    }

    // Helper for search
    bool search(Node* node, int value) const {
        if (!node) return false;
        if (value == node->value) return true;
        if (value < node->value)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

    // Helper for find minimum value node
    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // Helper for remove
    Node* remove(Node* node, int value) {
        if (!node) return nullptr;
        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            // Node found
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
                // Two children: get inorder successor
                Node* temp = findMin(node->right);
                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
        }
        return node;
    }

    // Helper for in-order display
    void display(Node* node) const {
        if (!node) return;
        display(node->left);
        std::cout << node->value << " ";
        display(node->right);
    }

    // Helper to deallocate memory
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    Set() : root(nullptr) {}

    ~Set() {
        clear(root);
    }

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
};
