#pragma once
#include "Ship.hpp"

class Battleship : public Ship {
public:
    Battleship(string name)
        : Ship(name, 3, 500, 1000, 200, 'B') {}

    void attack(Ship* target) override {
        cout << name << " is attacking " << target->getName() << "!" << endl;
        target->takeDamage(power);
    }

    void display() const override {
        cout << "Battleship: " << name << " | HP: " << health << endl;
    }
};




