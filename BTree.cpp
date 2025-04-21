#include "BTree.hpp"


using namespace std;
using namespace std::chrono;



BTreeNode::BTreeNode(int t, bool leaf) : t(t), leaf(leaf), n(0) {
    keys = new int[2 * t - 1];
    children = new BTreeNode *[2 * t];
}

BTreeNode::~BTreeNode() {
    for (int i = 0; i <= n; ++i) {
        if (!leaf && children[i])
            delete children[i];
    }
    delete[] keys;
    delete[] children;
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
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++;
}

int BTreeNode::search(int k, int& iterations) {
    int i = 0;
    while (i < n && k > keys[i]) {
        i++;
        iterations++;
    }

    if (i < n && keys[i] == k) {
        iterations++;
        return i;
    }

    if (leaf) return -1;

    return children[i]->search(k, iterations);
}



BTree::BTree() : Ship("BTree", 7, 200, 120, 730, 'T'), root(nullptr), t(BTREE_T) {
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
        set.insert(val);
    }

    for (int i = 0; i < set.getSize(); ++i) {
        insert(set.getElement(i));
    }
}

BTree::~BTree() {
    destroyTree(root);
}

void BTree::destroyTree(BTreeNode* node) {
    if (node) delete node;
}

void BTree::insert(int k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k) i++;
            s->children[i]->insertNonFull(k);

            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

int BTree::search(int k) {
    lastIterations = 0;
    foundLastValue = false;

    auto start = high_resolution_clock::now();
    if (root && root->search(k, lastIterations) != -1)
        foundLastValue = true;
    auto stop = high_resolution_clock::now();

    lastSearchTime = duration<double, std::milli>(stop - start).count();

    return lastIterations;
}

int BTree::getPower() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int target = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
    int iterations = search(target);
    return iterations > 0 ? DAMAGE_CONSTANT / iterations : 0;
}

void BTree::printReport() {
    cout << "[Search Result] Value was " << (foundLastValue ? "found." : "not found.") << "\n";
    cout << "[Damage] " << getPower() << "\n";
    cout << "Last search time (ms): " << lastSearchTime << "\n";
    cout << "Last iterations: " << lastIterations << "\n";
}