#pragma once
#include "Ship.hpp"
#include "Battleship.hpp"
#include "Cruiser.hpp"
#include "Destroyer.hpp"
#include "Carrier.hpp"
#include "Brownie.hpp"

class ShipFactory {
public:

    enum class ShipType {
        Battleship = 1,
        Cruiser,
        Destroyer,
        Carrier,
        Brownie
    };

    static Ship* createShip(ShipType type) {
        switch (type) {
            case ShipType::Battleship:
                return new Battleship("Battleship");
            case ShipType::Cruiser:
                return new Cruiser("Cruiser");
            case ShipType::Destroyer:
                return new Destroyer("Destroyer");
            case ShipType::Carrier:
                return new Carrier("Carrier");
            case ShipType::Brownie:
                return new Brownie();
            default:
                return nullptr;
        }
    }

    

    static ShipType fromInt(int value) {
        switch (value) {
            case 1: return ShipType::Battleship;
            case 2: return ShipType::Cruiser;
            case 3: return ShipType::Destroyer;
            case 4: return ShipType::Carrier;
            case 5: return ShipType::Brownie;
            default: throw invalid_argument("Valor inválido para ShipType: " + to_string(value));
        }
    }

    static Ship* createShip(int choice) {
        try {
            ShipType type = fromInt(choice);
            return createShip(type);  // Llama a la versión con enum
        } catch (const std::exception& e) {
            cerr << e.what() << endl;
            return nullptr;
        }
    }
};
