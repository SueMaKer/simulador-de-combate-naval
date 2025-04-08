#pragma once
#include "Ship.hpp"
#include <vector>

class Carrier : public Ship {

public:
    Carrier(string name)
        : Ship(name, 12, 600, 900, 100, 'A') {}

    void attack(Ship* target) override {
        cout << name << " is attacking " << target->getName() << "!" << endl;
        target->takeDamage(power);

    }

    void display() const override {
        cout << "Carrier: " << name << " | HP: " << health << endl;
    }
};
