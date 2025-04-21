#include "Player.hpp"

Player::Player(const std::string& name) : name(name), money(1000), health(100), actionPoints(3) {}

std::string Player::getName() const {
    return name;
}

int Player::getMoney() const {
    return money;
}

int Player::getHealth() const {
    return health;
}

int Player::getPoints() const {
    return actionPoints;
}

Board& Player::getBoard() {
    return board;
}

const Fleet& Player::getFleet() const {
    return board.getConstFleet();
}

Fleet& Player::getFleet(int rand) {
    return board.getFleet();
}

bool Player::isAlive() const {
    return health > 0;
}

bool Player::canAfford(int amount) const {
    return money >= amount;
}

void Player::addShip(Ship* ship) {
    board.getFleet().addShip(ship);
}

bool Player::spendMoney(int amount) {
    if (!canAfford(amount)) return false;
    money -= amount;
    return true;
}

void Player::addMoney(int currency) {
    money += currency;
}

void Player::setHealth(int newHealth) {
    health = newHealth;
}

void Player::resetPoints() {
    actionPoints = 3;
}

void Player::decreasePoints() {
    if (actionPoints > 0) --actionPoints;
}