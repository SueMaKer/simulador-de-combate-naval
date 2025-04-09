#include <iostream>
#include <chrono>
#include <random>

const int NUM_OF_ELEMENTS = 1000; // Number of elements in the list
const double DAMAGE_CONSTANT = 10000.0;

class Node {
public:
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class Brownie {    //Creating the list, searching through it, measuring time and iteration count and calculating damage.
private: 
    Node* head;
    int currentSize;
    double lastSearchTime; // in milliseconds
    int lastIterations;
    bool foundLastValue;

public: //Initializes the list and immediately fills it with random values.
    Brownie() : head(nullptr), currentSize(0), lastSearchTime(0), lastIterations(0), foundLastValue(false) {
        populateList();
    }

    ~Brownie() {
        clear();
    }

    void populateList() {
        clear();
        std::mt19937 rng(std::random_device{}()); //initializes a Mersenne Twister random number generator (rng) using a random seed from your system's hardware entropy source.
        std::uniform_int_distribution<int> dist(1, NUM_OF_ELEMENTS * 5); //Uses a random number generator to generate NUM_OF_ELEMENTS values between 1 and 5000.

        for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
            int val = dist(rng);
            insertAtEnd(val);
        }
    }

    void insertAtEnd(int value) { //Adds a new node with the given value to the end of the list.
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
        ++currentSize;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = nullptr;
        currentSize = 0;
    }

    void search(int target) {
        lastIterations = 0;
        foundLastValue = false;

        auto start = std::chrono::high_resolution_clock::now();

        Node* temp = head;
        while (temp) {
            ++lastIterations;
            if (temp->value == target) {
                foundLastValue = true;
                break;
            }
            temp = temp->next;
        }

        auto end = std::chrono::high_resolution_clock::now();
        lastSearchTime = std::chrono::duration<double, std::milli>(end - start).count();
    }

    double calculateDamage() const {        //Less iterations = higher damage.
        return lastIterations > 0 ? DAMAGE_CONSTANT / lastIterations : 0.0;
    }

    void printReport() const {
        std::cout << "[Search Result] Value was " << (foundLastValue ? "found." : "not found.") << "\n";
        std::cout << "[Damage] " << calculateDamage() << "\n";
        std::cout << "Current size: " << currentSize << "\n";
        std::cout << "Last search time (ms): " << lastSearchTime << "\n";
        std::cout << "Last iterations: " << lastIterations << "\n";
    }
};

/* int main() {
    Brownie brownie;

    int targetValue = 123; // You can change this to test different values
    brownie.search(targetValue);
    brownie.printReport();

    return 0;
} */
