#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ship {
    protected:
        string name;
        int size;
        int price;
        int health;
        int power;
        char id;  // Para identificar el barco en el tablero
    
    public:
        Ship(string name, int size, int price, int health, int power, char id)
            : name(name), size(size), price(price), health(health), power(power), id(id) {}
    
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
    
        string getName() const { return name; }
        int getHealth() const { return health; }
        bool isDestroyed() const { return health <= 0; }
        int getSize() const { return size; }
        int getPrice() const { return price; }
        char getID() const { return id; }  
        int getPower() const {return power;}
    };