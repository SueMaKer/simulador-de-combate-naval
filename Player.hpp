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
    Player(const std::string& name);

    std::string getName() const;
    int getMoney() const;
    int getHealth() const;
    int getPoints() const;

    Board& getBoard();
    const Fleet& getFleet() const;
    Fleet& getFleet(int rand); 

    bool isAlive() const;
    bool canAfford(int amount) const;

    void addShip(Ship* ship);

    bool spendMoney(int amount);
    void addMoney(int currency);
    void setHealth(int newHealth);
    void resetPoints();
    void decreasePoints();
};