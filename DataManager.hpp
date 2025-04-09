#pragma once
#include "Player.hpp"
#include <vector>
#include <string>
#include <limits>
#include "ShipFactory.hpp"

class DataManager {
public:
    // Mostrar información de un jugador
    void showPlayerInfo(const Player& player) const {
        std::cout << "=============Info==============\n";
        std::cout << "Player: " << player.getName() << "\n";
        std::cout << "Money: " << player.getMoney() << "\n";
        std::cout << "Health: " << player.getHealth() << "\n";
        std::cout << "Fleet size: " << player.getFleet().getSize() << "\n";
        std::cout << "=============Fleet===============\n";
        player.getFleet().displayFleet();
    }

    // Mostrar información del jugador actual
    void showCurrentPlayerInfo(const Player& player) const {
        showPlayerInfo(player);  // Mostrar solo la información del jugador actual
    }

    // Mostrar información de todos los jugadores
    void showAllPlayersInfo(const std::vector<Player>& players) const {
        for (const auto& player : players) {
            showPlayerInfo(player);
        }
    }

    // Mostrar el tablero del jugador
    void showPlayerBoard(Player& player) const {
        std::cout << "=============Player's Board==============\n";
        player.getBoard().display();  // Suponiendo que la clase Player tiene un método `getBoard`
    }

    int showOptions() {
        std::cout << "=============Actions==============\n";
        std::cout << "1. Buy Battleship\n";
        std::cout << "2. Upgrade Battleship\n";
        std::cout << "3. Move Battleship\n";
        std::cout << "4. Attack!\n";
        std::cout << "5. Surrender\n";
        std::cout << "==================================\n";
        return askInt("What would you like to do? :", 1, 5);
    }

    // Solicitar string
    std::string askString(const std::string& message) const {
        std::string input;
        std::cout << message;
        std::getline(std::cin, input);
        return input;
    }

    // Solicitar número entero
    int askInt(const std::string& message, int min, int max) const {
        int number;
        while (true) {
            std::cout << message;
            std::cin >> number;

            if (std::cin.fail() || number < min || number > max) {
                std::cin.clear(); // limpia error
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpia buffer
                std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpia buffer
                return number;
            }
        }
    }

    // Solicitar nuevo barco
    Ship* askShipToCreate() {
        std::cout << "Choose the type of ship to buy:\n";
        std::cout << "1. Battleship (Cost: 100)\n";
        std::cout << "2. Destroyer (Cost: 80)\n";
        std::cout << "3. Submarine (Cost: 60)\n";

        int option;
        std::cin >> option;
        std::string name = askString("Name your Battleship!");
        return ShipFactory::createShip(option, name);
    }

    // Mostrar un mensaje
    void showMessage(const std::string& message) const {
        std::cout << message << std::endl;
    }

    // Cambiar entre los jugadores
    void switchTurn(Player& currentPlayer, Player& nextPlayer) const {
        std::cout << "Switching turn...\n";
        showMessage("It's now " + nextPlayer.getName() + "'s turn.");
        // Aquí podrías agregar lógica para pasar el turno al siguiente jugador
    }

    
};