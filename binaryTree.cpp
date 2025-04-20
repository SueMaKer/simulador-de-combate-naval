#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Clase análoga a BTreeNode, pero para búsqueda binaria sobre array ordenado
class BinarySearchNode {
public:
    vector<int> data;

    void insert(int key);
    bool remove(int key);
    int binarySearch(int key, int& iterations);
    void traverse();
};

// Clase análoga a BTree, que interactúa con el "nodo" de array
class BinarySearchArray {
public:
    BinarySearchNode* root;

    BinarySearchArray() {
        root = new BinarySearchNode();
    }

    void insert(int key) {
        root->insert(key);
    }

    bool remove(int key) {
        return root->remove(key);
    }

    void traverse() {
        root->traverse();
    }

    int search(int key, int& iterations) {
        return root->binarySearch(key, iterations);
    }
};

// Implementaciones

void BinarySearchNode::insert(int key) {
    auto pos = lower_bound(data.begin(), data.end(), key);
    data.insert(pos, key);
}

bool BinarySearchNode::remove(int key) {
    auto pos = lower_bound(data.begin(), data.end(), key);
    if (pos != data.end() && *pos == key) {
        data.erase(pos);
        return true;
    }
    return false;
}

int BinarySearchNode::binarySearch(int key, int& iterations) {
    int left = 0;
    int right = static_cast<int>(data.size()) - 1;
    iterations = 0;

    while (left <= right) {
        iterations++;
        int mid = left + (right - left) / 2;

        if (data[mid] == key)
            return mid;
        else if (data[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void BinarySearchNode::traverse() {
    for (int val : data)
        cout << val << " ";
    cout << endl;
}

// Función con métricas de búsqueda
int searchWithMetrics(BinarySearchArray& arr, int key) {
    int iterations = 0;
    auto start = high_resolution_clock::now();
    int index = arr.search(key, iterations);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(end - start).count();

    if (index != -1)
        cout << key << " encontrado en el índice " << index;
    else
        cout << key << " no encontrado";

    cout << " tras " << iterations << " iteraciones.\n";
    cout << "Tiempo de búsqueda: " << duration << " nanosegundos.\n";

    return iterations;
}

// Main para probar
int main() {
    BinarySearchArray arr;
    for (int i = 0; i < 10; i++) {
        arr.insert(i * 2);  // Insertar pares: 0, 2, 4, ..., 18
    }

    cout << "Contenido del array: ";
    arr.traverse();

    searchWithMetrics(arr, 8);
    cout << endl;

    searchWithMetrics(arr, 9);
    cout << endl;

    arr.insert(9);
    cout << "Después de insertar 9: ";
    arr.traverse();

    arr.remove(4);
    cout << "Después de eliminar 4: ";
    arr.traverse();

    return 0;
}
