#include "Board.hpp"

void Board::display() const {
    // Mostrar el tablero con las coordenadas de las filas y columnas
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";  // Imprimir las coordenadas de las columnas
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";  // Imprimir las coordenadas de las filas
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == nullptr) {
                cout << "~ ";  // Casilla vacía
            } else {
                cout << board[i][j]->getID() << " ";  // Mostrar la ID del barco
            }
        }
        cout << endl;
    }
}

void Board::displayHitBoard() const {
    // Mostrar el tablero de hits con las coordenadas de las filas y columnas
    cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";  // Imprimir las coordenadas de las columnas
    }
    cout << endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << i << " ";  // Imprimir las coordenadas de las filas
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (hitBoard[i][j] == nullptr) {
                cout << "~ ";  // Casilla sin hit
            } else {
                cout << hitBoard[i][j]->getID() << " ";  // Mostrar la ID del barco al que le dio
            }
        }
        cout << endl;
    }
}

bool Board::placeShip(Ship* ship) {
    int row, col;
    char orientation;

    // Mostrar el tablero actual
    cout << "Current Board:" << endl;
    display();

    bool placed = false;
    while (!placed) {
        // Solicitar la posición inicial y la orientación del barco
        cout << "Enter the starting row for " << ship->getName() << " (size " << ship->getSize() << "): ";
        cin >> row;
        cout << "Enter the starting column for " << ship->getName() << " (size " << ship->getSize() << "): ";
        cin >> col;
        cout << "Enter orientation (h for horizontal, v for vertical): ";
        cin >> orientation;

        // Validar las coordenadas
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
            cout << "Invalid coordinates. Please enter values within the range of the board (0 to " << BOARD_SIZE - 1 << ")." << endl;
            continue;
        }

        // Verificar que la orientación sea válida
        if (orientation != 'h' && orientation != 'v') {
            cout << "Invalid orientation. Use 'h' for horizontal and 'v' for vertical." << endl;
            continue;
        }

        bool horizontal = (orientation == 'h');

        // Validar si el barco cabe en la posición indicada
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

            // Colocar el barco
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

            // Colocar el barco
            for (int i = 0; i < ship->getSize(); i++) {
                board[row + i][col] = ship;  // Colocar el puntero al barco en el tablero
            }
            placed = true;
        }
        ship->setOrientation(orientation);
        ship->setPosX(row);
        ship->setPosY(col);
        // Mostrar el tablero después de colocar el barco
        cout << "Current Board:" << endl;
        display();
    }
    
    return true;
}

bool Board::moveShip() {
    int row, col;
    char orientation;

    // Mostrar el tablero actual
    cout << "Current Board:" << endl;
    display();  // Mostrar el tablero con las posiciones actuales de los barcos

    // Mostrar los barcos y sus IDs para que el jugador elija cuál mover
    cout << "Your Fleet:" << endl;
    fleet.displayFleet();  // Mostrar los barcos de la flota con sus IDs

    char shipID;
    cout << "Enter the ID of the ship you want to move: ";
    cin >> shipID;

    // Buscar el barco por ID en la flota
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

    // Verificar si el barco está destruido
    if (selectedShip->isDestroyed()) {
        cout << "The ship " << selectedShip->getName() << " is destroyed and cannot be moved." << endl;
        return false;
    }

    // Pedir nuevas coordenadas para el barco
    cout << "Enter the new starting row for " << selectedShip->getName() << ": ";
    cin >> row;
    cout << "Enter the new starting column for " << selectedShip->getName() << ": ";
    cin >> col;
    cout << "Enter orientation (h for horizontal, v for vertical): ";
    cin >> orientation;

    // Validación de coordenadas
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        cout << "Invalid coordinates. Please enter values within the range of the board (0 to " << BOARD_SIZE - 1 << ")." << endl;
        return false;
    }

    bool horizontal = (orientation == 'h');

    // Verificar si el barco cabe en la nueva posición
    if (horizontal) {
        if (col + selectedShip->getSize() > BOARD_SIZE) {
            cout << "The ship does not fit horizontally on the board." << endl;
            return false;
        }

        // Validar que no haya partes de otros barcos en la nueva ubicación
        for (int i = 0; i < selectedShip->getSize(); i++) {
            if (board[row][col + i] != nullptr && board[row][col + i]->getID() != selectedShip->getID()) {
                cout << "The new position is blocked by another ship at position (" 
                     << row << ", " << col + i << ")." << endl;
                return false;
            }
        }

        // Eliminar el barco de la posición anterior
        for (int i = 0; i < selectedShip->getSize(); i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (board[j][k] == selectedShip) {
                        board[j][k] = nullptr;
                    }
                }
            }
        }

        // Colocar el barco en la nueva posición
        for (int i = 0; i < selectedShip->getSize(); i++) {
            board[row][col + i] = selectedShip;
        }
    } else {  // Vertical
        if (row + selectedShip->getSize() > BOARD_SIZE) {
            cout << "The ship does not fit vertically on the board." << endl;
            return false;
        }

        // Validar que no haya partes de otros barcos en la nueva ubicación
        for (int i = 0; i < selectedShip->getSize(); i++) {
            if (board[row + i][col] != nullptr && board[row + i][col]->getID() != selectedShip->getID()) {
                cout << "The new position is blocked by another ship at position (" 
                     << row + i << ", " << col << ")." << endl;
                return false;
            }
        }

        // Eliminar el barco de la posición anterior
        for (int i = 0; i < selectedShip->getSize(); i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (board[j][k] == selectedShip) {
                        board[j][k] = nullptr;
                    }
                }
            }
        }

        // Colocar el barco en la nueva posición
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

    displayHitBoard();  // Muestra el tablero de ataques

    // Solicitar coordenadas al jugador
    std::cout << "Enter the coordinates:\n";
    std::cout << "Row: ";
    std::cin >> row;
    std::cout << "Col: ";
    std::cin >> col;

    // Verificar si la posición es válida
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        std::cout << "Invalid coordinates. Please enter values within the range of the board (0 to " << BOARD_SIZE - 1 << ")." << std::endl;
        return false;
    }

    // Verificar si la posición ya ha sido atacada
    if (hitBoard[row][col] != nullptr) {
        std::cout << "This position has already been attacked." << std::endl;
        return false;
    }

    // Realizar el ataque en el tablero enemigo
    Ship* attackedShip = enemyBoard.getShipAt(row, col);
    if (attackedShip != nullptr) {
        hitBoard[row][col] = attackedShip;  
        
        // Realizar daño al barco atacado
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
        attackedShip->takeDamage(10);  // Aplica el daño al barco

        // Verificar si el barco está destruido
        if (attackedShip->isDestroyed()) {
            cout << attackedShip->getName() << " has been destroyed!" << endl;
        }
        board[row][col] = nullptr;  // Después de recibir el disparo, la casilla se queda vacía
        return true;
    } else {
        cout << "Miss." << endl;
        return false;
    }
}

bool Board::allShipsSunk() const {
    // Verificar si todos los barcos están destruidos
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != nullptr && !board[i][j]->isDestroyed()) {
                return false;  // Encontramos un barco que no está destruido
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
