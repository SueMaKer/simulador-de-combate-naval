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
    TurnManager(Player& p1, Player& p2, DataManager& dm) 
        : player1(p1), player2(p2), dm(dm) {}

    void playTurn(int currentPlayerIndex) {

        Player& currentPlayer = currentPlayerIndex == 0 ? player1 : player2;
        Player& enemyPlayer   = currentPlayerIndex == 0 ? player2 : player1;

        int actionsLeft = 3;
        bool turnOver = false;
        currentPlayer.addMoney(CURRENCY);
        std::cout << "You received " << CURRENCY << "\n";
        while (actionsLeft > 0 && !turnOver) {
            dm.showPlayerInfo(currentPlayer);
            std::cout << "You have " << actionsLeft << " actions left.\n";

            int option = dm.showOptions();

            switch(option) {
                case 1:
                    buyShip(currentPlayer);
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
                    showBoard(currentPlayer);
                    break;
                case 6:
                    showHitBoard(currentPlayer);
                    break;
                case 7:
                    surrender(currentPlayer);
                    exit(0);
                    break;
                default:
                    std::cout << "Invalid Option.\n";
                    break;
            }

            if (actionsLeft == 0) {
                std::cout << "End of turn.\n";
                turnOver = true;
            }
            int wait = dm.askInt("Press 1 to continue: ", 1, 1);
            dm.clearScreen();
        }

    }

    void showBoard(Player& player){
        dm.clearScreen();
        dm.showMessage("=====Board=====");
        player.getBoard().display();
    }

    void showHitBoard(Player& player){
        dm.clearScreen();
        dm.showMessage("=====Hitboard=====");
        player.getBoard().displayHitBoard();
    }
    
    void buyShip(Player& player) {
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
        player.getBoard().getFleet().displayFleet();
        int ship = dm.askInt("Select your ship to upgrade: ", 1, player.getFleet(1).getSize());
        player.getFleet(1).upgradeShip(--ship);
    }

    void attack(Player& attacker, Player& defender) {
        attacker.getBoard().getFleet().displayFleet();
        int ship = dm.askInt("Select your Ship: ", 1, attacker.getFleet(1).getSize());
        int damage = attacker.getFleet(1).getShipPower(--ship);
        if(attacker.getBoard().attack(defender.getBoard(), damage)){
            std::cout << "Damage dealt: " << damage <<".\n";
        } 
    }

    void surrender(Player& player) {
        std::cout << player.getName() << " surrendered.\n";
        exit(0);
    }

    bool isMyTurn(const string& playerName) const {
    return dm.getCurrentTurn() == playerName;
    }

    
};
