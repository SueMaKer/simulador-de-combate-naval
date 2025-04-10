#pragma once
#include "Ship.hpp"
#include "Battleship.hpp"
#include "Cruiser.hpp"
#include "Destroyer.hpp"
#include "Carrier.hpp"
#include "Brownie.hpp"

class ShipFactory {
public:
    static Ship* createShip(int choice) {
        switch (choice) {
            case 1: return new Battleship("Battleship");
            case 2: return new Cruiser("Cruiser");
            case 3: return new Destroyer("Destroyer");
            case 4: return new Carrier("Carrier");
            case 5: return new Brownie();
            default: return nullptr;
        }
    }
};