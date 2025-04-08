#pragma once
#include "Ship.hpp"
#include "Battleship.hpp"
#include "Cruiser.hpp"
#include "Destroyer.hpp"
#include "Carrier.hpp"

class ShipFactory {
public:
    static Ship* createShip(int choice, const std::string& name) {
        switch (choice) {
            case 1: return new Battleship(name);
            case 2: return new Cruiser(name);
            case 3: return new Destroyer(name);
            case 4: return new Carrier(name);
            default: return nullptr;
        }
    }
};