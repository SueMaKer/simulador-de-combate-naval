#pragma once
#include "Ship.hpp"

class Battleship : public Ship {
public:
    Battleship(string name)
        : Ship(name, 3, 500, 1000, 200, 'B') {}

    void display() const override {
        cout << "Battleship: " << name << " | HP: " << health << endl;
    }
};




