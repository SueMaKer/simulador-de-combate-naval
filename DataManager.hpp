#pragma once
#include "Player.hpp"
#include <filesystem>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <chrono>
#include <thread>
#include "ShipFactory.hpp"
using namespace std;

const string DROPBOX_DIR = "/home/emanuel-ramirez/Dropbox/NavalWarfare/"; // Adjust to your system

const string STATE_FILE        = DROPBOX_DIR + "state.txt";
const string PLAYER1_SHIPS     = DROPBOX_DIR + "player1_ships.txt";
const string PLAYER2_SHIPS     = DROPBOX_DIR + "player2_ships.txt";
const string PLAYER1_SHOTS     = DROPBOX_DIR + "player1_shots.txt";
const string PLAYER2_SHOTS     = DROPBOX_DIR + "player2_shots.txt";

class DataManager {
private:
    string player;
    bool isPlayer1;

public:
    

    // Mostrar información de un jugador
    void showPlayerInfo(const Player& player) const {
        cout << "=============Info==============\n";
        cout << "Player: " << player.getName() << "\n";
        cout << "Money: " << player.getMoney() << "\n";
        cout << "Health: " << player.getHealth() << "\n";
        cout << "Fleet size: " << player.getFleet().getSize() << "\n";
        cout << "=============Fleet===============\n";
        player.getFleet().displayFleet();
    }

    // Mostrar información del jugador actual
    void showCurrentPlayerInfo(const Player& player) const {
        showPlayerInfo(player);  // Mostrar solo la información del jugador actual
    }

    // Mostrar información de todos los jugadores
    void showAllPlayersInfo(const vector<Player>& players) const {
        for (const auto& player : players) {
            showPlayerInfo(player);
        }
    }

    // Mostrar el tablero del jugador
    void showPlayerBoard(Player& player) const {
        cout << "=============Player's Board==============\n";
        player.getBoard().display();  // Suponiendo que la clase Player tiene un método `getBoard`
    }

    int showOptions() {
        cout << "=============Actions==============\n";
        cout << "1. Buy Ship\n";
        cout << "2. Upgrade Ship\n";
        cout << "3. Move Ship\n";
        cout << "4. Attack!\n";
        cout << "5. Show my board\n";
        cout << "6. Show my hitboard\n";
        cout << "7. Surrender\n";
        cout << "==================================\n";
        return askInt("What would you like to do? :", 1, 7);
    }

    // Solicitar string
    string askString(const string& message) const {
        string input;
        cout << message;
        getline(cin, input);
        return input;
    }

    // Solicitar número entero
    int askInt(const string& message, int min, int max) const {
        int number;
        while (true) {
            cout << message;
            cin >> number;

            if (cin.fail() || number < min || number > max) {
                cin.clear(); // limpia error
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia buffer
                cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia buffer
                return number;
            }
        }
    }

    // Solicitar nuevo barco
    Ship* askShipToCreate() {
        cout << "Choose the type of ship to buy:\n";
        cout << "1. Battleship (Cost: 100)\n";
        cout << "2. Destroyer (Cost: 80)\n";
        cout << "3. Submarine (Cost: 60)\n";
        cout << "4. Carrier (Cost: 60)\n";
        cout << "5. Brownie (Cost: 150)\n";
        int option;
        cin >> option;
        
        return ShipFactory::createShip(option);
    }

    // Mostrar un mensaje
    void showMessage(const string& message) const {
        cout << message << endl;
    }

    // Cambiar entre los jugadores
    void switchTurn(Player& currentPlayer, Player& nextPlayer) const {
        cout << "Switching turn...\n";
        showMessage("It's now " + nextPlayer.getName() + "'s turn.");
        // Aquí podrías agregar lógica para pasar el turno al siguiente jugador
    }

    void clearScreen() {
        system("clear");
    }

    // Multiplayer-related functions

    bool fileExists(const string& path) {
        return filesystem::exists(path);
    }

    void verifyAndSetupFiles() {
        // Create directory if it doesn't exist
        if (!filesystem::exists(DROPBOX_DIR)) {
            filesystem::create_directories(DROPBOX_DIR);
        }

        // Setup state file
        if (!fileExists(STATE_FILE)) {
            ofstream outFile(STATE_FILE);
            outFile << "turn:player1\n";
            outFile << "last_shot:-1,-1\n";
            outFile << "result:none\n";
        }

        // Setup player files
        if (!fileExists(PLAYER1_SHIPS)) ofstream(PLAYER1_SHIPS).close();
        if (!fileExists(PLAYER2_SHIPS)) ofstream(PLAYER2_SHIPS).close();
        if (!fileExists(PLAYER1_SHOTS)) ofstream(PLAYER1_SHOTS).close();
        if (!fileExists(PLAYER2_SHOTS)) ofstream(PLAYER2_SHOTS).close();
    }

    string getCurrentTurn() const {
        ifstream file(STATE_FILE);
        string line;
        while (getline(file, line)) {
            if (line.rfind("turn:", 0) == 0) { 
                return line.substr(5); // salta "turn:"
            }
        }
        return "unknown";
    }

    void setCurrentTurn(const string& playerTurn) {
        ifstream inFile(STATE_FILE);
        stringstream buffer;
        string line;
        while (getline(inFile, line)) {
            if (line.rfind("turn:", 0) == 0) {
                buffer << "turn:" << playerTurn << "\n";
            } else {
                buffer << line << "\n";
            }
        }
        inFile.close();
        ofstream outFile(STATE_FILE);
        outFile << buffer.str();
    }   


    string getPlayer() const { return player;}

    void initializeGameWithPlayers() {
        string player1;

        // Crear archivo si no existe
        if (!filesystem::exists(STATE_FILE)) {
            string player1Name;
            cout << "You are the first player! Enter your name: ";
            getline(cin, player1);
            player = player1;
            isPlayer1 = true;

            ofstream out(STATE_FILE);
            out << "player1:" << player1 << "\n";
            out << "player2:\n";  // Aún no se une el segundo jugador
            out << "turn:" << player1 << "\n";
            out << "last_shot:-1,-1\n";
            out << "result:none\n";
            out.close();

            cout << "✅ Waiting for second player to join...\n";

            // Espera hasta que el segundo jugador ingrese
            while (true) {
                this_thread::sleep_for(chrono::seconds(2));
                ifstream in(STATE_FILE);
                string line;
                while (getline(in, line)) {
                    if (line.rfind("player2:", 0) == 0 && line.length() > 8) {
                        cout << "🎮 Second player joined! Starting game...\n";
                        return;
                    }
                }
            }
        } else {
            // Archivo ya existe, ver si el segundo jugador ya se unió
            fstream file(STATE_FILE, ios::in | ios::out);
            string line, content;
            string player2;

            bool player2Exists = false;

            while (getline(file, line)) {
                content += line + "\n";
                if (line.rfind("player2:", 0) == 0 && line.length() > 8) {
                    player2Exists = true;
                    player2 = line.substr(8);
                }
            }

            if (player2Exists) {
                cout << "🎮 Welcome back, " << player2 << "! Game already started.\n";
                return;
            }

            // No hay player2, pedir nombre y agregarlo
            string player2Name;
            cout << "You are the second player! Enter your name: ";
            getline(cin, player2Name);
            player = player2Name;
            isPlayer1 = false;


            // Reemplazar línea de player2
            size_t pos = content.find("player2:");
            if (pos != string::npos) {
                content.replace(pos, content.find("\n", pos) - pos, "player2:" + player2Name);
            }

            // Reescribir el archivo
            ofstream out(STATE_FILE);
            out << content;
            out.close();

            cout << "✅ Joined as second player. Game is ready to start!\n";
        }
    }

    string getPlayer1Name() const {
        ifstream file(STATE_FILE);
        string line;
        while (getline(file, line)) {
            if (line.rfind("player1:", 0) == 0) {
                return line.substr(8); // salta "player1:"
            }
        }
        return "";
    }

    string getPlayer2Name() const {
        ifstream file(STATE_FILE);
        string line;
        while (getline(file, line)) {
            if (line.rfind("player2:", 0) == 0) {
                return line.substr(8); // salta "player2:"
            }
        }
        return "";
    }

    void cleanDropboxContents() {
        if (!filesystem::exists(DROPBOX_DIR)) return;

        for (const auto& entry : filesystem::directory_iterator(DROPBOX_DIR)) {
            try {
                if (filesystem::is_directory(entry)) {
                    filesystem::remove_all(entry); // Elimina subcarpetas
                } else {
                    filesystem::remove(entry);     // Elimina archivos
                }
            } catch (const filesystem::filesystem_error& e) {
                // Ignorar errores
            }
        }
    }

    bool isThisPlayer1(){
        return isPlayer1;
    }

};
