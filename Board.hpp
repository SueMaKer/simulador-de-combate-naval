#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Fleet.hpp"

using namespace std;

const int BOARD_SIZE = 10;  // Board size (10x10)

/*
 * Board class represents the game board for placing and managing ships.
 * It handles ship placement, movement, and board display for both player view and hit tracking.
 */
class Board {
    private:
        Ship* board[BOARD_SIZE][BOARD_SIZE];      // Main board with ship positions
        Ship* hitBoard[BOARD_SIZE][BOARD_SIZE];   // Board to track hits
        vector<Ship*> ships;                      // Ships placed on the board
        Fleet fleet;                              // Fleet object to manage player's ships

    public:
        /*
         * Constructor: Initializes the board and hit board with nullptr.
         */
        Board() {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    board[i][j] = nullptr;
                    hitBoard[i][j] = nullptr;
                }
            }
        }

        /*
         * Displays the current board with ship positions.
         * '~' represents empty cells.
         */
        void display() const;

        /*
         * Displays the hit board showing successful hits.
         * '~' represents cells without hits.
         */
        void displayHitBoard() const;

        /*
         * Places a ship on the board.
         * Prompts the user to input starting coordinates and orientation.
         * Validates placement rules (bounds, overlapping).
         *
         * @param ship Pointer to the ship to place.
         * @return true if the ship was placed successfully.
         */
        bool placeShip(Ship* ship);

        /*
         * Allows the player to move a ship already placed on the board.
         * Prompts the user to select a ship by ID and input new position and orientation.
         * Validates new position.
         *
         * @return true if the ship was moved successfully.
         */
        bool moveShip();

        bool attack(Board& enemyBoard, const int damage);

        bool receiveShot(int row, int col);

        bool allShipsSunk() const;

        Ship* getShipAt(int row, int col) const;

        const Fleet& getConstFleet() const;

        Fleet& getFleet();
};