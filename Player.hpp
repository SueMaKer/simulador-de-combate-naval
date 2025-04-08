#pragma once
#include <vector>
#include <string>
#include "Fleet.hpp"
#include "Board.hpp"

class Player {
private:
    int actionPoints;
    std::string name;
    int money;
    int health;
    Board board;

public:
    Player(const std::string& name)
        : name(name), health(100), money(2000), actionPoints(3) {}

    // Getters
    const std::string getName() const{
        return name;
    }
    const int getHealth() const{
        return health;
    }
    const int getMoney() const{
        return money;
    }
    const Fleet& getFleet() const {
        return board.getConstFleet();
    }
    Board& getBoard(){ 
        return board; 
    }
    const int getPoints() const {
        return actionPoints;
    }
    // Setters
    void setHealth(int health) {
        this->health = health;
    }

    // Funciones utilitarias
    void addShip(Ship* ship){
        board.getFleet().addShip(ship);
    }

    bool spendMoney(int amount) {
        if (money >= amount) {
            money -= amount;
            return true; // Se pudo gastar
        } else {
            std::cout << "Not enough money!" << std::endl;
            return false; // No se pudo gastar
        }
    }
    void resetPoints(){
        actionPoints = 3;
    }

    void decreasePoints(){
        --actionPoints;
    }
    
};