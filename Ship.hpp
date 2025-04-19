#pragma once
#include <iostream>
#include <string>
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
    
    public:
        Ship(string name, int size, int price, int health, int power, char id)
            : name(name), size(size), price(price), health(health), power(power), id(id) {}
        
        Ship(){}
    
        virtual ~Ship() = default;
    
        virtual void display() const {
            // Mostrar información del barco
            cout << "Ship: " << name << ", Health: " << health << ", Power: " << power << endl;
        }
    
        virtual void takeDamage(int dmg) {
            health -= dmg;
            if (health < 0) health = 0;
        }

        virtual void upgradeShip(){
            cout << "not implemented!" << endl;
        }
         // Métodos getters
        string getName() const { return name; }
        char getOrientation() const { return orientation; }
        int getPosX() const { return posx; }
        int getPosY() const { return posy; }
        int getSize() const { return size; }
        int getPrice() const { return price; }
        int getHealth() const { return health; }
        virtual int getPower() { return power; }
        char getID() const { return id; }
        bool isDestroyed() const { return health <= 0; }

        // Métodos setters
        void setName(const string& newName) { name = newName; }
        void setOrientation(char newOrientation) { orientation = newOrientation; }
        void setPosX(int newPosX) { posx = newPosX; }
        void setPosY(int newPosY) { posy = newPosY; }
        void setSize(int newSize) { size = newSize; }
        void setPrice(int newPrice) { price = newPrice; }
        void setHealth(int newHealth) { health = newHealth; }
        void setPower(int newPower) { power = newPower; }
        void setID(char newID) { id = newID; }
    };