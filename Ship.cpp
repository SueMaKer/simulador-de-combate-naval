#include "Ship.hpp"

Ship::Ship(string name, int size, int price, int health, int power, char id)
    : name(name), size(size), price(price), health(health), power(power), id(id) ,lastSearchTime(0), lastIterations(0), foundLastValue(false) {}

Ship::Ship() : name("Unnamed"), size(0), price(0), health(0), power(0), id(' ') {}

void Ship::display() const {
    cout << "Ship: " << name << ", Health: " << health << ", Power: " << power << endl;
}

void Ship::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

void Ship::upgradeShip() {
    cout << "Upgrade logic not implemented!" << endl;
}


void Ship::printReport() {
    std::ofstream outFile("Report.txt", std::ios::app); // ← modo append

    if (outFile.is_open()) {
        outFile << "------------"<<name<<"--------------\n";
        outFile << "[Search Result] Value was " << (foundLastValue ? "found." : "not found.") << "\n";
        outFile << "[Damage] " << getPower() << "\n";
        outFile << "Last search time (ms): " << lastSearchTime << "\n";
        outFile << "Last iterations: " << lastIterations << "\n";
        outFile << "------------------------\n\n";
        outFile.close();
    } else {
        std::cerr << "Error: Could not open Report.txt for writing.\n";
    }
}

// Métodos getters
string Ship::getName() const { return name; }
char Ship::getOrientation() const { return orientation; }
int Ship::getPosX() const { return posx; }
int Ship::getPosY() const { return posy; }
int Ship::getSize() const { return size; }
int Ship::getPrice() const { return price; }
int Ship::getHealth() const { return health; }
int Ship::getPower() { return power; }
char Ship::getID() const { return id; }

bool Ship::isDestroyed() const { return health <= 0; }

// Métodos setters
void Ship::setName(const string& newName) { name = newName; }
void Ship::setOrientation(char newOrientation) { orientation = newOrientation; }
void Ship::setPosX(int newPosX) { posx = newPosX; }
void Ship::setPosY(int newPosY) { posy = newPosY; }
void Ship::setSize(int newSize) { size = newSize; }
void Ship::setPrice(int newPrice) { price = newPrice; }
void Ship::setHealth(int newHealth) { health = newHealth; }
void Ship::setPower(int newPower) { power = newPower; }
void Ship::setID(char newID) { id = newID; }