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
        for (int i = 0; i < size; ++i) {
            std::cout << i+1 << ": ";
            ships[i]->display();
        }
    }
    int getSize() const {
        return size;
    }
    const int getShipPower(int index){
        return ships[index]->getPower();
    }

    void upgradeShip(int index){
        ships[index]->upgradeShip();
    } 
    vector<Ship *> getShips(){
        return ships;
    }
};
