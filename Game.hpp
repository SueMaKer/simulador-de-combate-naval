#pragma once
#include "Player.hpp"
#include "TurnManager.hpp"
#include "DataManager.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

class Game {
private:
    std::vector<Player> players;
    DataManager dm;
    TurnManager* turnManager;  
    int currentPlayerIndex;
    bool gameOver;

public:
    Game();  
    ~Game();  

    void nextTurn();
    bool checkGameOver();
    void start();
    void setGameMode();
};