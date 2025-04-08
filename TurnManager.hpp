#pragma once
#include "Player.hpp"
#include "DataManager.hpp"
#include <iostream>

class TurnManager {
private:
    Player& player1;
    Player& player2;
    DataManager& dm;

public:
    TurnManager(Player& p1, Player& p2, DataManager& dm) 
        : player1(p1), player2(p2), dm(dm) {}

    void mostrarOpciones() const {
        std::cout << "=============Actions==============\n";
        std::cout << "1. Buy Ship\n";
        std::cout << "2. Upgrade Ship\n";
        std::cout << "3. Move Ship\n";
        std::cout << "4. Attack!\n";
        std::cout << "5. Surrender\n";
        std::cout << "==================================\n";
    }

    void playTurn(int currentPlayerIndex) {
        Player& currentPlayer = currentPlayerIndex == 0 ? player1 : player2;
        Player& enemyPlayer   = currentPlayerIndex == 0 ? player2 : player1;

        int actionsLeft = 3;
        bool turnOver = false;

        while (actionsLeft > 0 && !turnOver) {
            dm.showPlayerInfo(currentPlayer);
            std::cout << "You have " << actionsLeft << " actions left.\n";
            mostrarOpciones();

            int option;
            std::cin >> option;

            switch(option) {
                case 1:
                    comprarBarco(currentPlayer);
                    actionsLeft--;
                    break;
                case 2:
                    upgradeShip(currentPlayer);
                    actionsLeft--;
                    break;
                case 3:
                    currentPlayer.getBoard().moveShip();
                    actionsLeft--;
                    break;
                case 4:
                    attack(currentPlayer, enemyPlayer);
                    actionsLeft--;
                    break;
                case 5:
                    surrender(currentPlayer);
                    turnOver = true;
                    break;
                default:
                    std::cout << "Invalid Option.\n";
                    break;
            }

            if (actionsLeft == 0) {
                std::cout << "End of turn.\n";
                turnOver = true;
            }
        }
    }

    void comprarBarco(Player& player) {
        Ship* ship = dm.askShipToCreate();
        if (!ship) return;

        if (player.spendMoney(ship->getPrice()) && player.getBoard().placeShip(ship)) {
            player.addShip(ship);
        } else {
            std::cout << "Failed to buy ship.\n";
            delete ship;
        }
    }

    void upgradeShip(Player& player) {
        std::cout << "Upgrading Ship...\n";
    }

    void attack(Player& attacker, Player& defender) {
        attacker.getBoard().attack(defender.getBoard()); 
    }

    void surrender(Player& player) {
        std::cout << player.getName() << " surrendered.\n";
        exit(0);
    }
};
