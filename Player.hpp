#pragma once
#include "Board.hpp"
#include <string>

class Player {
private:
    std::string name;
    int money;
    int health;
    int actionPoints;
    Board board;

public:
    Player(const std::string& name) : name(name), money(2000), health(100), actionPoints(3) {}

    std::string getName() const { return name; }
    int getMoney() const { return money; }
    int getHealth() const { return health; }
    int getPoints() const { return actionPoints; }

    Board& getBoard() { return board; }
    const Fleet& getFleet() const { return board.getConstFleet(); }
    Fleet& getFleet(int rand) {return board.getFleet();}

    bool isAlive() const { return health > 0; }
    bool canAfford(int amount) const { return money >= amount; }

    void addShip(Ship* ship) { board.getFleet().addShip(ship); }

    bool spendMoney(int amount) {
        if (!canAfford(amount)) return false;
        money -= amount;
        return true;
    }

    void setHealth(int newHealth) { health = newHealth; }
    void resetPoints() { actionPoints = 3; }
    void decreasePoints() { if (actionPoints > 0) --actionPoints; }
};