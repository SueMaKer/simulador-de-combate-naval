#pragma once 

#include <random>
#include "Ship.hpp"

class Node {
public:
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class Brownie : public Ship{    //Creating the list, searching through it, measuring time and iteration count and calculating damage.
private: 
    Node* head;
    int currentSize;

public: //Initializes the list and immediately fills it with random values.
    Brownie() : head(nullptr), currentSize(0), Ship("Brownie", 4, 240, 100, 650, 'B'){
        populateList();
    }

    
    ~Brownie() {
        clear();
    }

    void populateList() {
        clear();
        srand(static_cast<unsigned int>(time(nullptr))); 
        for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
            int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;
  
            insertAtEnd(val);
        }
    }

    void insertAtEnd(int value) { 
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

    int getPower() override{        //Less iterations = higher damage.
        search(23);
        return lastIterations > 0 ? DAMAGE_CONSTANT / lastIterations : 0.0;
    }

};