#pragma once
#include "Ship.hpp"

class Cruiser : public Ship {
public:
    Cruiser(string name)
        : Ship(name, 8, 400, 800, 150, 'C') {}
        
    void display() const override {
        cout << "Cruiser: " << name << " | HP: " << health << endl;
    }
};