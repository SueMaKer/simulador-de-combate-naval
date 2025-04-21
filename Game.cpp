#include "Game.hpp"

Game::Game() : currentPlayerIndex(0), gameOver(false) {

    setGameMode();

    if (dm.isLocal()) {
        std::string player1Name = dm.askString("Player 1 Name: ");
        std::string player2Name = dm.askString("Player 2 Name: ");

        players.push_back(Player(player1Name));
        players.push_back(Player(player2Name));

        // Crear barco inicial a cada jugador
        for (auto& player : players) {
            dm.showPlayerInfo(player);
            Ship* newShip = dm.askShipToCreate();
            if (newShip) {
                player.addShip(newShip);
                player.getBoard().placeShip(newShip);
            }
        }

        // Inicializamos el TurnManager pasándole los dos jugadores y DataManager
        turnManager = new TurnManager(players[0], players[1], dm);
        dm.clearScreen();

    } else {
        dm.showMessage("Multiplayer");
        dm.initializeGameWithPlayers();
        dm.verifyAndSetupFiles();
        players.push_back(Player(dm.getPlayer1Name()));
        players.push_back(Player(dm.getPlayer2Name()));
        turnManager = new TurnManager(players[0], players[1], dm);
        dm.showMessage("Done correctly");
    }
}

Game::~Game() {
    dm.cleanDropboxContents();
    delete turnManager;
}

void Game::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

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

void Game::start() {
    std::cout << "Welcome to Naval Warfare!\n";
    if (dm.isLocal()) {
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
        // Modo multiplayer
        std::string myTurn = dm.isThisPlayer1() ? dm.getPlayer1Name() : dm.getPlayer2Name();
        std::string otherTurn = dm.isThisPlayer1() ? dm.getPlayer2Name() : dm.getPlayer1Name();
        int myIndex = dm.isThisPlayer1() ? 0 : 1;
        int otherIndex = dm.isThisPlayer1() ? 1 : 0;

        while (!gameOver) {
            Player& currentPlayer = players[myIndex];
            Player& otherPlayer = players[otherIndex];

            // ⏳ Esperar mi turno
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

            // Cambiar el turno en Dropbox
            dm.setCurrentTurn(otherTurn);
        }
    }
}

void Game::setGameMode() {
    if (dm.askInt("Select Game Mode\n1. Local\n2. Multiplayer\n", 1, 2) == 1) {
        dm.setMultiplayer(false);
    } else {
        dm.setMultiplayer(true);
    }
}