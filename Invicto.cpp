#pragma once
#include <iostream>
#include <chrono>
#include <random>
#include "Ship.hpp"
using namespace std;
using namespace std::chrono;

int NUM_OF_ELEMENTS = 1000;
int DAMAGE_CONSTANT = 800;

// Nodo del BTree (sin cambios)
class BTreeNode {
public:
    int *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;

    BTreeNode(int t, bool leaf);

    void traverse();
    BTreeNode *search(int k, int &iterations);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *y);

    friend class BTree;
};

// Clase BTree como hija de Ship
class BTree : public Ship {
private:
    BTreeNode *root;
    int t;
    double lastSearchTime;
    int lastIterations;
    bool foundLastValue;

public:
    BTree(int t = 3) 
        : Ship("BTree", 5, 200, 120, 700, 'T'), root(nullptr), t(t), lastSearchTime(0), lastIterations(0), foundLastValue(false) {
        populateTree();
    }

    ~BTree() {
        // Nota: Se podría implementar una función recursiva para liberar memoria
        // pero se omite aquí porque el foco es conectar con Ship
    }

    void populateTree() {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(1, NUM_OF_ELEMENTS * 5);

        for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
            int val = dist(rng);
            insert(val);
        }
    }

    void insert(int k);
    void search(int k);
    
    int getPower() override {
        search(23);
        return lastIterations > 0 ? DAMAGE_CONSTANT / lastIterations : 0.0;
    }

    void printReport() {
        std::cout << "[Search Result] Value was " << (foundLastValue ? "found." : "not found.") << "\n";
        std::cout << "[Damage] " << getPower() << "\n";
        std::cout << "Last search time (ms): " << lastSearchTime << "\n";
        std::cout << "Last iterations: " << lastIterations << "\n";
    }
};

// Implementación de BTreeNode (sin cambios)
BTreeNode::BTreeNode(int t, bool leaf) {
    this->t = t;
    this->leaf = leaf;
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];
    n = 0;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf)
        C[i]->traverse();
}

BTreeNode *BTreeNode::search(int k, int &iterations) {
    int i = 0;
    while (i < n && k > keys[i]) {
        i++;
        iterations++;
    }
    if (i < n && keys[i] == k) {
        iterations++;
        return this;
    }
    if (leaf)
        return nullptr;
    return C[i]->search(k, iterations);
}

void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = (s->keys[0] < k) ? 1 : 0;
            s->C[i]->insertNonFull(k);
            root = s;
        } else
            root->insertNonFull(k);
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf)
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];
    C[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n++;
}

// Método de búsqueda con métricas para el BTree que se conecta a getPower
void BTree::search(int k) {
    lastIterations = 0;
    foundLastValue = false;

    auto start = high_resolution_clock::now();
    BTreeNode *result = root ? root->search(k, lastIterations) : nullptr;
    auto stop = high_resolution_clock::now();

    lastSearchTime = duration<double, std::milli>(stop - start).count();
    foundLastValue = (result != nullptr);
}
