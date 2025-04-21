#pragma once
#include "Ship.hpp"

#include "Brownie.hpp"
#include "Splay.hpp"
#include "RedBlack.hpp"
#include "BinaryTree.hpp"
#include "BTree.hpp"

class ShipFactory {
public:

    enum class ShipType {
        Splay = 1,
        RedBlack,
        BinaryTree,
        Brownie,
        BTree,
    };

    static Ship* createShip(ShipType type) {
        switch (type) {
            case ShipType::Splay:
                return new Splay();
            case ShipType::RedBlack:
                return new RedBlack();
            case ShipType::BinaryTree:
                return new BinaryTree();
            case ShipType::Brownie:
                return new Brownie();
            case ShipType::BTree:
                return new BTree();    
            default:
                return nullptr;
        }
    }

    

    static ShipType fromInt(int value) {
        switch (value) {
            case 1: return ShipType::Splay;
            case 2: return ShipType::RedBlack;
            case 3: return ShipType::BinaryTree;
            case 4: return ShipType::Brownie;
            case 5: return ShipType::BTree;
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
