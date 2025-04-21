#include "Set.hpp"

// Constructor
Set::Set() : root(nullptr) {}

// Destructor
Set::~Set() {
    clear(root);
}

// Método recursivo para insertar un valor en el árbol
Set::Node* Set::insert(Node* node, int value) {
    if (!node) return new Node(value);
    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    return node;
}

// Método recursivo para buscar un valor en el árbol
bool Set::search(Node* node, int value) const {
    if (!node) return false;
    if (value == node->value) return true;
    if (value < node->value)
        return search(node->left, value);
    else
        return search(node->right, value);
}

// Encuentra el valor mínimo en el árbol (más a la izquierda)
Set::Node* Set::findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Método recursivo para eliminar un valor en el árbol
Set::Node* Set::remove(Node* node, int value) {
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

// Método recursivo para mostrar los valores del conjunto en orden
void Set::display(Node* node) const {
    if (!node) return;
    display(node->left);
    std::cout << node->value << " ";
    display(node->right);
}

// Método recursivo para limpiar el árbol (destruir los nodos)
void Set::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

// Método recursivo para obtener el tamaño del conjunto
int Set::getSize(Node* node) const {
    if (!node) return 0;
    return 1 + getSize(node->left) + getSize(node->right);
}

// Método recursivo para obtener el elemento en una posición específica
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

// Método para insertar un valor en el conjunto
void Set::insert(int value) {
    if (!search(value)) {
        root = insert(root, value);
        std::cout << value << " inserted.\n";
    } else {
        std::cout << value << " already exists.\n";
    }
}

// Método para buscar un valor en el conjunto
bool Set::search(int value) const {
    return search(root, value);
}

// Método para eliminar un valor del conjunto
void Set::remove(int value) {
    if (search(value)) {
        root = remove(root, value);
        std::cout << value << " removed.\n";
    } else {
        std::cout << value << " not found.\n";
    }
}

// Método para mostrar los valores del conjunto en orden
void Set::display() const {
    std::cout << "Set contents: ";
    display(root);
    std::cout << "\n";
}

// Método para obtener el tamaño del conjunto
int Set::getSize() const {
    return getSize(root);
}

// Método para obtener un elemento en una posición específica
int Set::getElement(int index) const {
    int size = getSize();
    if (index < 0 || index >= size) {
        std::cerr << "Index out of bounds\n";
        return -1; // o lanza una excepción si prefieres
    }

    int counter = 0;
    int result = -1;
    getElementAt(root, counter, index, result);
    return result;
}