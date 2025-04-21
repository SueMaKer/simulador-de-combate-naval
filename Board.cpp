#include "Board.hpp"

void Board::display() const {
    
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";  
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";  
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == nullptr) {
                cout << "~ ";  
            } else {
                cout << board[i][j]->getID() << " ";  
            }
        }
        cout << endl;
    }
}

void Board::displayHitBoard() const {
    
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";  
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";  
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (hitBoard[i][j] == nullptr) {
                cout << "~ ";  
            } else {
                cout << hitBoard[i][j]->getID() << " "; 
            }
        }
        cout << endl;
    }
}

bool Board::placeShip(Ship* ship) {
    int row, col;
    char orientation;

    cout << "Current Board:" << endl;
    display();

    bool placed = false;
    while (!placed) {
       
        cout << "Enter the starting row for " << ship->getName() << " (size " << ship->getSize() << "): ";
        cin >> row;
        cout << "Enter the starting column for " << ship->getName() << " (size " << ship->getSize() << "): ";
        cin >> col;
        cout << "Enter orientation (h for horizontal, v for vertical): ";
        cin >> orientation;

        
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            cout << "Invalid coordinates. Please enter values within the range of the board (0 to " << BOARD_SIZE - 1 << ")." << endl;
            continue;
        }

        
        if (orientation != 'h' && orientation != 'v') {
            cout << "Invalid orientation. Use 'h' for horizontal and 'v' for vertical." << endl;
            continue;
        }

        bool horizontal = (orientation == 'h');

      
        if (horizontal) {
            if (col + ship->getSize() > BOARD_SIZE) {
                cout << "The ship does not fit horizontally on the board." << endl;
                continue;
            }
            for (int i = 0; i < ship->getSize(); i++) {
                if (board[row][col + i] != nullptr) {
                    cout << "There is already a ship at position (" << row << ", " << col + i << ")." << endl;
                    continue;
                }
            }

           
            for (int i = 0; i < ship->getSize(); i++) {
                board[row][col + i] = ship;  
            }

            placed = true;
        } else {
            if (row + ship->getSize() > BOARD_SIZE) {
                cout << "The ship does not fit vertically on the board." << endl;
                continue;
            }
            for (int i = 0; i < ship->getSize(); i++) {
                if (board[row + i][col] != nullptr) {
                    cout << "There is already a ship at position (" << row + i << ", " << col << ")." << endl;
                    continue;
                }
            }

       
            for (int i = 0; i < ship->getSize(); i++) {
                board[row + i][col] = ship;  
            }
            placed = true;
        }
        ship->setOrientation(orientation);
        ship->setPosX(row);
        ship->setPosY(col);
     
        cout << "Current Board:" << endl;
        display();
    }
    
    return true;
}

bool Board::placeShipAt(Ship* ship, int row, int col, char orientation) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cerr << "Invalid coordinates (" << row << "," << col << "). Out of board bounds." << endl;
        return false;
    }

    bool horizontal = (orientation == 'h' || orientation == 'H');


    if (horizontal) {
        if (col + ship->getSize() > BOARD_SIZE) {
            cerr << "Ship doesn't fit horizontally at (" << row << "," << col << ")." << endl;
            return false;
        }
        for (int i = 0; i < ship->getSize(); ++i) {
            if (board[row][col + i] != nullptr) {
                cerr << "Collision detected at (" << row << "," << col + i << ")." << endl;
                return false;
            }
        }
      
        for (int i = 0; i < ship->getSize(); ++i) {
            board[row][col + i] = ship;
        }
    } else {
        if (row + ship->getSize() > BOARD_SIZE) {
            cerr << "Ship doesn't fit vertically at (" << row << "," << col << ")." << endl;
            return false;
        }
        for (int i = 0; i < ship->getSize(); ++i) {
            if (board[row + i][col] != nullptr) {
                cerr << "Collision detected at (" << row + i << "," << col << ")." << endl;
                return false;
            }
        }
      
        for (int i = 0; i < ship->getSize(); ++i) {
            board[row + i][col] = ship;
        }
    }

    return true;
}

bool Board::moveShip() {
    int row, col;
    char orientation;

  
    cout << "Current Board:" << endl;
    display();  

    cout << "Your Fleet:" << endl;
    fleet.displayFleet();  

    char shipID;
    cout << "Enter the ID of the ship you want to move: ";
    cin >> shipID;

   
    Ship* selectedShip = nullptr;
    for (auto s : fleet.getShips()) {
        if (s->getID() == shipID) {
            selectedShip = s;
            break;
        }
    }

    if (!selectedShip) {
        cout << "Ship with ID " << shipID << " not found in your fleet." << endl;
        return false;
    }

  
    if (selectedShip->isDestroyed()) {
        cout << "The ship " << selectedShip->getName() << " is destroyed and cannot be moved." << endl;
        return false;
    }

    
    cout << "Enter the new starting row for " << selectedShip->getName() << ": ";
    cin >> row;
    cout << "Enter the new starting column for " << selectedShip->getName() << ": ";
    cin >> col;
    cout << "Enter orientation (h for horizontal, v for vertical): ";
    cin >> orientation;

 
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cout << "Invalid coordinates. Please enter values within the range of the board (0 to " << BOARD_SIZE - 1 << ")." << endl;
        return false;
    }

    bool horizontal = (orientation == 'h');

    
    if (horizontal) {
        if (col + selectedShip->getSize() > BOARD_SIZE) {
            cout << "The ship does not fit horizontally on the board." << endl;
            return false;
        }

     
        for (int i = 0; i < selectedShip->getSize(); i++) {
            if (board[row][col + i] != nullptr && board[row][col + i]->getID() != selectedShip->getID()) {
                cout << "The new position is blocked by another ship at position (" 
                     << row << ", " << col + i << ")." << endl;
                return false;
            }
        }

        
        for (int i = 0; i < selectedShip->getSize(); i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (board[j][k] == selectedShip) {
                        board[j][k] = nullptr;
                    }
                }
            }
        }

      
        for (int i = 0; i < selectedShip->getSize(); i++) {
            board[row][col + i] = selectedShip;
        }
    } else {  
        if (row + selectedShip->getSize() > BOARD_SIZE) {
            cout << "The ship does not fit vertically on the board." << endl;
            return false;
        }


        for (int i = 0; i < selectedShip->getSize(); i++) {
            if (board[row + i][col] != nullptr && board[row + i][col]->getID() != selectedShip->getID()) {
                cout << "The new position is blocked by another ship at position (" 
                     << row + i << ", " << col << ")." << endl;
                return false;
            }
        }


        for (int i = 0; i < selectedShip->getSize(); i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (board[j][k] == selectedShip) {
                        board[j][k] = nullptr;
                    }
                }
            }
        }


        for (int i = 0; i < selectedShip->getSize(); i++) {
            board[row + i][col] = selectedShip;
        }

    }
    
    selectedShip->setOrientation(orientation);
    selectedShip->setPosX(row);
    selectedShip->setPosY(col);
    return true;
}

bool Board::attack(Board& enemyBoard, const int damage) {
    int row, col;

    displayHitBoard();  
    std::cout << "Enter the coordinates:\n";
    std::cout << "Row: ";
    std::cin >> row;
    std::cout << "Col: ";
    std::cin >> col;

    
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        std::cout << "Invalid coordinates. Please enter values within the range of the board (0 to " << BOARD_SIZE - 1 << ")." << std::endl;
        return false;
    }

    if (hitBoard[row][col] != nullptr) {
        std::cout << "This position has already been attacked." << std::endl;
        return false;
    }

   
    Ship* attackedShip = enemyBoard.getShipAt(row, col);
    if (attackedShip != nullptr) {
        hitBoard[row][col] = attackedShip;  
        
       
        attackedShip->takeDamage(damage);

        std::cout << "Hit! The ship's health is now " << attackedShip->getHealth() << std::endl;
        
        if (attackedShip->getHealth() == 0) {
            std::cout << "The ship has been destroyed!" << std::endl;
        }

        return true;
    } else {
        hitBoard[row][col] = nullptr;  
        std::cout << "Miss!" << std::endl;
        return true;
    }
}

bool Board::receiveShot(int row, int col) {
    if (board[row][col] != nullptr) {
        Ship* attackedShip = board[row][col];
        cout << "Hit on " << attackedShip->getName() << "!" << endl;
        attackedShip->takeDamage(10);  

      
        if (attackedShip->isDestroyed()) {
            cout << attackedShip->getName() << " has been destroyed!" << endl;
        }
        board[row][col] = nullptr;  
        return true;
    } else {
        cout << "Miss." << endl;
        return false;
    }
}

bool Board::allShipsSunk() const {
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != nullptr && !board[i][j]->isDestroyed()) {
                return false;  
            }
        }
    }
    return true;
}

Ship* Board::getShipAt(int row, int col) const {
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
        return board[row][col];
    }
    return nullptr;
}

const Fleet& Board::getConstFleet() const{
    return fleet;
}

Fleet& Board::getFleet() {
    return fleet;
}
