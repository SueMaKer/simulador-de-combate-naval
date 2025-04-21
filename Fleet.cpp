#include "Fleet.hpp"

void Fleet::addShip(Ship* ship) {
    ++size;
    ships.push_back(ship);
}

Ship* Fleet::findShip(const std::string& name) {
    for (auto s : ships) {
        if (s->getName() == name)
            return s;
    }
    return nullptr;
}

void Fleet::displayFleet() const {
    for (int i = 0; i < size; ++i) {
        std::cout << i + 1 << ": ";
        ships[i]->display();
    }
}

int Fleet::getSize() const {
    return size;
}

int Fleet::getShipPower(int index) {
    return ships[index]->getPower();
}

void Fleet::upgradeShip(int index) {
    ships[index]->upgradeShip();
}

std::vector<Ship*> Fleet::getShips() {
    return ships;
}

void Fleet::clearShips() {
    for (Ship* ship : ships) {
        delete ship;
    }
    ships.clear();
    size = 0;
}