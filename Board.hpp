#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Fleet.hpp"

using namespace std;

const int BOARD_SIZE = 10;  // Board size (10x10)


class Board {
    private:
        Ship* board[BOARD_SIZE][BOARD_SIZE];      // Main board with ship positions
        Ship* hitBoard[BOARD_SIZE][BOARD_SIZE];   // Board to track hits
        vector<Ship*> ships;                      // Ships placed on the board
        Fleet fleet;                              // Fleet object to manage player's ships

    public:
        
        Board() {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    board[i][j] = nullptr;
                    hitBoard[i][j] = nullptr;
                }
            }
        }

      
        void display() const;

       
        void displayHitBoard() const;

        
        bool placeShip(Ship* ship);

        
        bool moveShip();

        bool attack(Board& enemyBoard, const int damage);

        bool receiveShot(int row, int col);

        bool allShipsSunk() const;

        Ship* getShipAt(int row, int col) const;

        const Fleet& getConstFleet() const;

        Fleet& getFleet();

        bool placeShipAt(Ship* ship, int row, int col, char orientation);
};