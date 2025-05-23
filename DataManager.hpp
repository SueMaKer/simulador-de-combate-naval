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

const string DROPBOX_DIR = "/home/melissa/Dropbox/NavalWarfare/"; 

const string STATE_FILE        = DROPBOX_DIR + "state.txt";
const string PLAYER1_SHIPS     = DROPBOX_DIR + "player1_ships.txt";
const string PLAYER2_SHIPS     = DROPBOX_DIR + "player2_ships.txt";
const string PLAYER1_SHOTS     = DROPBOX_DIR + "player1_shots.txt";
const string PLAYER2_SHOTS     = DROPBOX_DIR + "player2_shots.txt";

class DataManager {
private:
    string player;
    bool isPlayer1;
    ShipFactory factory;
    bool multiplayer;
public:
    
    void setMultiplayer(bool gamemode) {
        multiplayer = gamemode;
    }

    bool isLocal() {
        return !multiplayer;
    }

    
    void showPlayerInfo(const Player& player) const {
        cout << "=============Info==============\n";
        cout << "Player: " << player.getName() << "\n";
        cout << "Money: " << player.getMoney() << "\n";
        cout << "Health: " << player.getHealth() << "\n";
        cout << "Fleet size: " << player.getFleet().getSize() << "\n";
        cout << "=============Fleet===============\n";
        player.getFleet().displayFleet();
    }

    
    void showCurrentPlayerInfo(const Player& player) const {
        showPlayerInfo(player);  // Mostrar solo la información del jugador actual
    }

  
    void showAllPlayersInfo(const vector<Player>& players) const {
        for (const auto& player : players) {
            showPlayerInfo(player);
        }
    }

    void showPlayerBoard(Player& player) const {
        cout << "=============Player's Board==============\n";
        player.getBoard().display();  
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

    
    string askString(const string& message) const {
        string input;
        cout << message;
        getline(cin, input);
        return input;
    }

    
    int askInt(const string& message, int min, int max) const {
        int number;
        while (true) {
            cout << message;
            cin >> number;

            if (cin.fail() || number < min || number > max) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                return number;
            }
        }
    }

    Ship* askShipToCreate() {
        cout << "Choose the type of ship to buy:\n";
        cout << "1. Splay (Cost: 200)\n";
        cout << "2. RedBlack (Cost: 220)\n";
        cout << "3. BinaryTree (Cost: 150)\n";
        cout << "4. BTree (Cost: 200)\n";
        cout << "5. Set (Cost: 150)\n";
        cout << "6. LinkedLink (Cost: 150)\n";
        int option;
        cin >> option;
        
        return ShipFactory::createShip(option);
    }

 
    void showMessage(const string& message) const {
        cout << message << endl;
    }

   
    void switchTurn(Player& currentPlayer, Player& nextPlayer) const {
        cout << "Switching turn...\n";
        showMessage("It's now " + nextPlayer.getName() + "'s turn.");
        
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
                return line.substr(5); 
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

       
        if (!filesystem::exists(STATE_FILE)) {
            string player1Name;
            cout << "You are the first player! Enter your name: ";
            getline(cin, player1);
            player = player1;
            isPlayer1 = true;

            ofstream out(STATE_FILE);
            out << "player1:" << player1 << "\n";
            out << "player2:\n";  
            out << "turn:" << player1 << "\n";
            out << "last_shot:-1,-1\n";
            out << "result:none\n";
            out.close();

            cout << "✅ Waiting for second player to join...\n";

          
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

     
            string player2Name;
            cout << "You are the second player! Enter your name: ";
            getline(cin, player2Name);
            player = player2Name;
            isPlayer1 = false;


        
            size_t pos = content.find("player2:");
            if (pos != string::npos) {
                content.replace(pos, content.find("\n", pos) - pos, "player2:" + player2Name);
            }

            
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
                return line.substr(8); 
            }
        }
        return "";
    }

    string getPlayer2Name() const {
        ifstream file(STATE_FILE);
        string line;
        while (getline(file, line)) {
            if (line.rfind("player2:", 0) == 0) {
                return line.substr(8); 
            }
        }
        return "";
    }

    void cleanDropboxContents() {
        if (!filesystem::exists(DROPBOX_DIR)) return;

        for (const auto& entry : filesystem::directory_iterator(DROPBOX_DIR)) {
            try {
                if (filesystem::is_directory(entry)) {
                    filesystem::remove_all(entry); 
                } else {
                    filesystem::remove(entry);     
                }
            } catch (const filesystem::filesystem_error& e) {
                
            }
        }
    }

    bool isThisPlayer1(){
        return isPlayer1;
    }

    void saveFleetToFile(bool player1, Player &player) {
        string path = player1 ? PLAYER1_SHIPS : PLAYER2_SHIPS;
        ofstream out(path);
        for (Ship* ship : player.getBoard().getFleet().getShips()) {
            out << ship->getSize() << ","
                << ship->getName() << ","
                << ship->getID() << ","
                << ship->getPower() << ","
                << ship->getHealth() << ","
                << ship->getPrice() << ","
                << ship->getOrientation() << ","
                << ship->getPosX() << ","
                << ship->getPosY() << "\n";
        }
        out.close();
    }

    Ship* createShipFromType(const string& name) {
        if (name == "Splay") return factory.createShip(1);
        if (name == "RedBlack") return factory.createShip(2);
        if (name == "BinaryTree") return factory.createShip(3);
        if (name == "Brownie") return factory.createShip(4);
        if (name == "BTree") return factory.createShip(5);
        cerr << "Tipo de nave desconocido: " << name << endl;
        return nullptr;
    }

    void loadFleetFromFile(bool player1, Player& player) {
        string path = player1 ? PLAYER1_SHIPS : PLAYER2_SHIPS;
        ifstream in(path);
        if (!in.is_open()) {
            cerr << "No se pudo abrir el archivo: " << path << endl;
            return;
        }

        player.getFleet(1).clearShips();  

        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            string name, id, orientation;
            int size, power, health, price, posX, posY;

         
            ss >> size; ss.ignore();
            getline(ss, name, ',');
            getline(ss, id, ',');
            ss >> power; ss.ignore();
            ss >> health; ss.ignore();
            ss >> price; ss.ignore();
            getline(ss, orientation, ',');
            ss >> posX; ss.ignore();
            ss >> posY;

            
            Ship* ship = createShipFromType(name);  
            if (!ship) continue;

            
            ship->setName(name);
            ship->setPower(power);
            ship->setHealth(health);
            ship->setSize(size);
            ship->setPrice(price);
            ship->setOrientation(orientation[0]);  
            ship->setPosX(posX);
            ship->setPosY(posY);

            
            player.getBoard().placeShipAt(ship, posX, posY, orientation[0]);
            player.getFleet(1).addShip(ship);
        }

        in.close();
    }

};
