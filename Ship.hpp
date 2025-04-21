#pragma once
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Set.hpp"
#include <iostream>
#include <string>
#include <fstream>

const int NUM_OF_ELEMENTS = 1000;
const double DAMAGE_CONSTANT = 1000.0;


using namespace std;

class Ship {
protected:
    string name;
    char orientation;
    int posx;
    int posy;
    int size;
    int price;
    int health;
    int power;
    char id;
    Set set;
    double lastSearchTime;
    int lastIterations;
    bool foundLastValue;

public:
    Ship(string name, int size, int price, int health, int power, char id);
    Ship();

    virtual ~Ship() = default;

    virtual void display() const;
    virtual void takeDamage(int dmg);
    virtual void upgradeShip();

    void printReport();
    

    // Métodos getters
    string getName() const;
    char getOrientation() const;
    int getPosX() const;
    int getPosY() const;
    int getSize() const;
    int getPrice() const;
    int getHealth() const;
    virtual int getPower();
    char getID() const;
    bool isDestroyed() const;

    // Métodos setters
    void setName(const string& newName);
    void setOrientation(char newOrientation);
    void setPosX(int newPosX);
    void setPosY(int newPosY);
    void setSize(int newSize);
    void setPrice(int newPrice);
    void setHealth(int newHealth);
    void setPower(int newPower);
    void setID(char newID);
};