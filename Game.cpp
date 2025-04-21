#include "Game.hpp"

// Constructor: Initializes the game depending on the selected mode (local or multiplayer)
Game::Game() : currentPlayerIndex(0), gameOver(false) {

    setGameMode(); // Ask the user to choose the game mode

    if (dm.isLocal()) {
        // Local mode: ask for player names and create initial ships
        std::string player1Name = dm.askString("Player 1 Name: ");
        std::string player2Name = dm.askString("Player 2 Name: ");

        players.push_back(Player(player1Name));
        players.push_back(Player(player2Name));

        // Each player creates their first ship
        for (auto& player : players) {
            dm.showPlayerInfo(player);
            Ship* newShip = dm.askShipToCreate();
            if (newShip) {
                player.addShip(newShip);
                player.getBoard().placeShip(newShip);
            }
        }

        // Initialize TurnManager with both players
        turnManager = new TurnManager(players[0], players[1], dm);
        dm.clearScreen();

    } else {
        // Multiplayer mode: setup game using Dropbox files
        dm.showMessage("Multiplayer");
        dm.initializeGameWithPlayers();
        dm.verifyAndSetupFiles();

        players.push_back(Player(dm.getPlayer1Name()));
        players.push_back(Player(dm.getPlayer2Name()));

        turnManager = new TurnManager(players[0], players[1], dm);
        dm.showMessage("Done correctly");
    }
}

// Destructor: Cleans up Dropbox files and deletes the TurnManager
Game::~Game() {
    dm.cleanDropboxContents();
    delete turnManager;
}

// Switch to the next player's turn
void Game::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

// Check if the game is over (only one or zero players left alive)
bool Game::checkGameOver() {
    int alive = 0;
    for (auto& player : players) {
        if (player.getHealth() > 0)
            alive++;
    }
    if (alive <= 1) {
        gameOver = true;
        return true;
    }
    return false;
}

// Start the main game loop (local or multiplayer)
void Game::start() {
    std::cout << "Welcome to Naval Warfare!\n";

    if (dm.isLocal()) {
        // Local game loop
        while (!gameOver) {
            Player& currentPlayer = players[currentPlayerIndex];
            std::cout << "\nIt's " << currentPlayer.getName() << "'s turn!\n";

            turnManager->playTurn(currentPlayerIndex);

            if (checkGameOver()) {
                std::cout << "Game Over! ";
                for (auto& player : players) {
                    if (player.getHealth() > 0) {
                        std::cout << player.getName() << " Wins!\n";
                    }
                }
            } else {
                nextTurn();
            }
        }

    } else {
        // Multiplayer game loop using Dropbox turn system
        std::string myTurn = dm.isThisPlayer1() ? dm.getPlayer1Name() : dm.getPlayer2Name();
        std::string otherTurn = dm.isThisPlayer1() ? dm.getPlayer2Name() : dm.getPlayer1Name();
        int myIndex = dm.isThisPlayer1() ? 0 : 1;
        int otherIndex = dm.isThisPlayer1() ? 1 : 0;

        while (!gameOver) {
            Player& currentPlayer = players[myIndex];
            Player& otherPlayer = players[otherIndex];

            // ⏳ Wait until it's this player's turn
            while (dm.getCurrentTurn() != myTurn) {
                dm.clearScreen();
                std::cout << "\nIt's " << otherPlayer.getName() << "'s turn!";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "."; std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "."; std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "."; std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            std::cout << "\nIt's your turn, " << currentPlayer.getName() << "!\n";

            turnManager->playTurn(myIndex);

            if (checkGameOver()) {
                std::cout << "🎉 Game Over! " << currentPlayer.getName() << " wins!\n";
                break;
            }

            // Set the next turn in Dropbox
            dm.setCurrentTurn(otherTurn);
        }
    }
}

// Ask the user to select the game mode: 1 (Local) or 2 (Multiplayer)
void Game::setGameMode() {
    if (dm.askInt("Select Game Mode\n1. Local\n2. Multiplayer\n", 1, 2) == 1) {
        dm.setMultiplayer(false);
    } else {
        dm.setMultiplayer(true);
    }
}