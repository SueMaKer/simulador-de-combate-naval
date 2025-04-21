#include "TurnManager.hpp"
#include "Ship.hpp"
#include <iostream>
#include <cstdlib>

#define CURRENCY 200

// TurnManager.cpp - Controls player turns and interactions during the game

// Constructor: Initializes TurnManager with two players and the DataManager for input/output.
TurnManager::TurnManager(Player& p1, Player& p2, DataManager& dm) 
    : player1(p1), player2(p2), dm(dm) {}

// Controls a single turn for the current player.
void TurnManager::playTurn(int currentPlayerIndex) {
    Player& currentPlayer = currentPlayerIndex == 0 ? player1 : player2;
    Player& enemyPlayer   = currentPlayerIndex == 0 ? player2 : player1;

    // In online mode, load fleets from file
    if(!dm.isLocal()){
        dm.loadFleetFromFile(dm.isThisPlayer1(), currentPlayer);
        dm.loadFleetFromFile(!dm.isThisPlayer1(), enemyPlayer);
    }

    int actionsLeft = 3;
    bool turnOver = false;
    currentPlayer.addMoney(CURRENCY);
    std::cout << "You received " << CURRENCY << "\n";

    // Player can perform up to 3 actions per turn
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

        // Save fleets in online mode
        if(!dm.isLocal()){
            dm.saveFleetToFile(dm.isThisPlayer1(), currentPlayer);
            dm.saveFleetToFile(!dm.isThisPlayer1(), enemyPlayer);
        }

        int wait = dm.askInt("Press 1 to continue: ", 1, 1);
        dm.clearScreen();
    }
}

// Displays the player's current board
void TurnManager::showBoard(Player& player) {
    dm.clearScreen();
    dm.showMessage("=====Board=====");
    player.getBoard().display();
}

// Displays the player's hit board (where they’ve attacked)
void TurnManager::showHitBoard(Player& player) {
    dm.clearScreen();
    dm.showMessage("=====Hitboard=====");
    player.getBoard().displayHitBoard();
}

// Allows the player to buy a new ship and place it on their board
void TurnManager::buyShip(Player& player) {
    Ship* ship = dm.askShipToCreate();
    if (!ship) return;

    if (player.spendMoney(ship->getPrice()) && player.getBoard().placeShip(ship)) {
        player.addShip(ship);
    } else {
        std::cout << "Failed to buy ship.\n";
        delete ship;
    }
}

// Upgrades a ship in the player's fleet
void TurnManager::upgradeShip(Player& player) {
    player.getBoard().getFleet().displayFleet();
    int ship = dm.askInt("Select your ship to upgrade: ", 1, player.getFleet(1).getSize());
    player.getFleet(1).upgradeShip(--ship);
}

// Handles attacking with a selected ship
void TurnManager::attack(Player& attacker, Player& defender) {
    attacker.getBoard().getFleet().displayFleet();
    int ship = dm.askInt("Select your Ship: ", 1, attacker.getFleet(1).getSize());
    int damage = attacker.getFleet(1).getShipPower(ship - 1);
    if(attacker.getBoard().attack(defender.getBoard(), damage)){
        std::cout << "Damage dealt: " << damage << ".\n";
        attacker.getFleet(1).setShipInfo(ship - 1);
    } 
}

// Ends the game if a player decides to surrender
void TurnManager::surrender(Player& player) {
    std::cout << player.getName() << " surrendered.\n";
    exit(0);
}

// Checks if it is the current player's turn (used in online mode)
bool TurnManager::isMyTurn(const std::string& playerName) const {
    return dm.getCurrentTurn() == playerName;
}
