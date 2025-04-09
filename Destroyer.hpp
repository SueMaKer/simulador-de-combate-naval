#pragma once
#include "Ship.hpp"
#include <unordered_set>

class Destroyer : public Ship {
    unordered_set<string> missiles;

public:
    Destroyer(string name)
        : Ship(name, 5, 300, 600, 120, 'D') {}

    void display() const override {
        cout << "Destroyer: " << name << " | HP: " << health << endl;
    }
};
