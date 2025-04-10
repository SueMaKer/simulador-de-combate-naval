#pragma once
#include "Player.hpp"
#include "TurnManager.hpp"
#include "DataManager.hpp"
#include <iostream>
#include <vector>
#include <string>

class Game {
private:
    std::vector<Player> players;
    DataManager dm;
    TurnManager* turnManager;  // Ahora es puntero porque se inicializa después
    int currentPlayerIndex;
    bool gameOver;

public:
    Game() : currentPlayerIndex(0), gameOver(false) {
        std::string player1Name = dm.askString("Player 1 Name: ");
        std::string player2Name = dm.askString("Player 2 Name: ");

        players.push_back(Player(player1Name));
        players.push_back(Player(player2Name));

        // Crear barco inicial a cada jugador
        for (auto& player : players) {
            dm.showPlayerInfo(player);
            Ship* newShip = dm.askShipToCreate();
            if (newShip) {
                player.addShip(newShip);
                player.getBoard().placeShip(newShip);
            }
        }

        // Inicializamos el TurnManager pasándole los dos jugadores y DataManager
        turnManager = new TurnManager(players[0], players[1], dm);
        dm.clearScreen();
    }

    ~Game() {
        delete turnManager;
    }

    void nextTurn() {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }

    bool checkGameOver() {
        int alive = 0;
        for (auto& player : players) {
            if (player.getHealth() > 0)
                alive++;
        }
        if (alive <= 1) {
            gameOver = true;
            return true;
        }
        return false;
    }

    void start() {
        std::cout << "Welcome to Naval Warfare!\n";

        while (!gameOver) {
            Player& currentPlayer = players[currentPlayerIndex];
            std::cout << "\nIt's " << currentPlayer.getName() << "'s turn!\n";

            turnManager->playTurn(currentPlayerIndex);

            if (checkGameOver()) {
                std::cout << "Game Over! ";
                for (auto& player : players) {
                    if (player.getHealth() > 0) {
                        std::cout << player.getName() << " Wins!\n";
                    }
                }
            } else {
                nextTurn();
            }
        }
    }
};
