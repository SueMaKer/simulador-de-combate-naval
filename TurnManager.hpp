#pragma once
#include "Player.hpp"
#include "DataManager.hpp"
#include <iostream>
#include <cstdlib>

#define CURRENCY  200

class TurnManager {
private:
    Player& player1;
    Player& player2;
    DataManager& dm;

public:
    TurnManager(Player& p1, Player& p2, DataManager& dm);

    void playTurn(int currentPlayerIndex);

    void showBoard(Player& player);
    void showHitBoard(Player& player);
    
    void buyShip(Player& player);
    void upgradeShip(Player& player);
    void attack(Player& attacker, Player& defender);
    void surrender(Player& player);

    bool isMyTurn(const std::string& playerName) const;
};