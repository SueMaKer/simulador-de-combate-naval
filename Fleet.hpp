#pragma once
#include "Ship.hpp"
#include <vector>

class Fleet {
    vector<Ship*> ships;
    int size = 0;
public:
    void addShip(Ship* ship) {
        ++size;
        ships.push_back(ship);
    }

    Ship* findShip(const string& name) {
        for (auto s : ships) {
            if (s->getName() == name)
                return s;
        }
        return nullptr;
    }

    void displayFleet() const {
        for (auto s : ships)
            s->display();
    }
    int getSize() const {
        return size;
    }

    vector<Ship *> getShips(){
        return ships;
    }
};
