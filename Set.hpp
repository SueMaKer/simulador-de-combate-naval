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

    Node* insert(Node* node, int value);
    bool search(Node* node, int value) const;
    Node* findMin(Node* node);
    Node* remove(Node* node, int value);
    void display(Node* node) const;
    void clear(Node* node);
    int getSize(Node* node) const;
    bool getElementAt(Node* node, int& counter, int index, int& result) const;

public:
    Set();
    ~Set();

    void insert(int value);
    bool search(int value) const;
    void remove(int value);
    void display() const;
    int getSize() const;
    int getElement(int index) const;
};