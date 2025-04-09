#pragma once
#include "Ship.hpp"
#include <vector>

class Carrier : public Ship {

public:
    Carrier(string name)
        : Ship(name, 12, 600, 900, 100, 'A') {}

    void display() const override {
        cout << "Carrier: " << name << " | HP: " << health << endl;
    }
};
