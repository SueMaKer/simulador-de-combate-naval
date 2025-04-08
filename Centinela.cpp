#include <iostream>
#include <set>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

const int NUM_OF_ELEMENTS = 1000;
const double DAMAGE_CONSTANT = 10000.0;

class Ship {
public:
    virtual void fill() = 0;
    virtual bool search(int target) = 0;
    virtual double calculateDamage() const = 0;
    virtual void upgrade(int units) = 0;
    virtual ~Ship() {}
};

class Centinela : public Ship {
private:
    std::set<int> elementRegistry;       // Tracks unique elements (NOT for searching)
    std::vector<int> dataStructure;      // Simulates real storage (used for search)
    int iterations = 0;
    double lastSearchTime = 0.0;

public:
    void fill() override {
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, NUM_OF_ELEMENTS * 10);

        while (elementRegistry.size() < NUM_OF_ELEMENTS) {
            int value = dist(rng);
            if (elementRegistry.insert(value).second) {
                dataStructure.push_back(value);
            }
        }
    }

    bool search(int target) override {
        iterations = 0;
        auto start = std::chrono::high_resolution_clock::now();

        // Simulated search - do NOT use set.find()
        for (int val : dataStructure) {
            ++iterations;
            if (val == target) {
                break;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        lastSearchTime = std::chrono::duration<double, std::milli>(end - start).count();

        // Check if element is actually in the registry (used for validation)
        return elementRegistry.count(target) > 0;
    }

    double calculateDamage() const override {
        return iterations == 0 ? 0.0 : DAMAGE_CONSTANT / iterations;
    }

    void upgrade(int units) override {
        std::mt19937 rng(std::random_device{}());
        for (int i = 0; i < units && !elementRegistry.empty(); ++i) {
            std::uniform_int_distribution<size_t> dist(0, dataStructure.size() - 1);
            int index = dist(rng);
            int value = dataStructure[index];

            // Remove from set and vector
            if (elementRegistry.erase(value)) {
                dataStructure.erase(dataStructure.begin() + index);
            }
        }
    }

    void printStatus() const {
        std::cout << "Current size: " << elementRegistry.size() << "\n";
        std::cout << "Last search time (ms): " << lastSearchTime << "\n";
        std::cout << "Last iterations: " << iterations << "\n";
    }
};

int main() {
    Centinela sentinelShip;
    sentinelShip.fill();

    int target = 123; // You can change this
    bool found = sentinelShip.search(target);

    std::cout << "[Search Result] Value " << target << (found ? " was found.\n" : " was NOT found.\n");
    std::cout << "[Damage] " << sentinelShip.calculateDamage() << "\n";

    sentinelShip.upgrade(5);
    sentinelShip.printStatus();

    return 0;
}
