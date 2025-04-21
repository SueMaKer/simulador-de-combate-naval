#include "SetShip.hpp"

SetShip::SetShip() : Ship("SetShip", 4, 150, 100, 500, 'S'){
    setSet();  // Initialize the Set with random values
}

void SetShip::setSet() {
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed for random number generation
    for (int i = 0; i < NUM_OF_ELEMENTS; ++i) {
        int val = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;  // Generate random values
        set.insert(val);  // Insert the value into the Set
    }
}

int SetShip::search(int key) {
    lastIterations = 0;
    foundLastValue = false;

    auto start = high_resolution_clock::now();  // Start measuring search time
    
    // Perform the search using the Set
    if (set.search(key)) {
        foundLastValue = true;  // If the value is found
    }

    // Set the number of iterations based on the Set size
    lastIterations = set.getSize();

    auto stop = high_resolution_clock::now();  // Stop measuring search time
    lastSearchTime = duration<double, std::milli>(stop - start).count();  // Calculate elapsed time

    return lastIterations;  // Return the number of iterations
}

int SetShip::getPower() {
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed for random number generation
    int target = (rand() % (NUM_OF_ELEMENTS * 5)) + 1;  // Generate a random target
    int iterations = search(target);  // Perform the search
    return iterations > 0 ? DAMAGE_CONSTANT / iterations : 0;  // Calculate damage based on search iterations
}