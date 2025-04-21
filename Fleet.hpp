#pragma once
#include "Ship.hpp"
#include <vector>
#include <iostream>

class Fleet {
private:
    std::vector<Ship*> ships;
    int size = 0;

public:
    void addShip(Ship* ship);

    Ship* findShip(const std::string& name);

    void displayFleet() const;

    int getSize() const;

    int getShipPower(int index);

    void upgradeShip(int index);

    std::vector<Ship*> getShips();

    void clearShips();

    void setShipInfo(int index);
};