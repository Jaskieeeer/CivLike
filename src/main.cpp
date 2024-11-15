#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Grid.h"
#include "../include/TurnManager.h"
#include "../include/Player.h"
#include "../include/Civilization.h"
#include "../include/RomanCiv.h"
#include "../include/Settler.h"
#include "../include/globals.h"
std::vector<std::pair<int, int>> generateSpawnPoints(int numPlayers, int gridWidth, int gridHeight) 
    {
        std::vector<std::pair<int, int>> spawnPoints;
        int sectionWidth = gridWidth / numPlayers;
        int sectionHeight = gridHeight / numPlayers;

        for (int i = 0; i < numPlayers; ++i) {
            int spawn_x = (std::rand() % sectionWidth) + (i * sectionWidth);
            int spawn_y = (std::rand() % sectionHeight) + (i * sectionHeight);
            spawnPoints.push_back(std::make_pair(spawn_x, spawn_y));
        }

        return spawnPoints;
    }
int main() {
    std::srand(std::time(0)); // Seed for random number generation

    TurnManager turnManager;
    Player player1("Alice", new RomanCiv());
    Player player2("Bob", new RomanCiv());
    
    std::vector<std::pair<int, int>> spawnPoints = generateSpawnPoints(2, globalGrid.getWidth(), globalGrid.getHeight());
    player1.addUnit(new Settler (spawnPoints[0].first, spawnPoints[0].second));
    player2.addUnit(new Settler (spawnPoints[1].first, spawnPoints[1].second)); 
    for (int i = 0; i < size(player2.units); ++i) {
        player2.units[i]->displayStatus();
    }
    bool isGameOver = false;
    player1.displayInfo();
    player2.displayInfo();
    player1.transformUnitIntoTown(1);
    player1.displayInfo();
    player1.getTown(1)->displayTownStatus();
    player1.loseTown(player1.getTown(1),&player2);
    player1.displayInfo();
    player2.displayInfo();
    player1.addUnit(new Settler ( spawnPoints[0].first, spawnPoints[0].second));
    player1.displayInfo();
    player1.transformUnitIntoTown(3);
    player1.displayInfo();
    // game loop
    // while (!isGameOver) {
    //     std::cout << "Player " << turnManager.getCurrentPlayer() << "'s turn\n";
        
    //     // Simulate a player action (for now, just a message)
    //     std::cout << "Player " << turnManager.getCurrentPlayer() << " is taking action...\n";
        
    //     // Skip turn logic for demonstration (could be based on conditions in your game)
    //     if (turnManager.getCurrentPlayer() == 1) {
    //         turnManager.skipTurn();  // For example, skip Player 1's turn
    //     }

    //     turnManager.nextTurn();  // Move to the next player's turn

    //     // Simulate game over condition (this is just an example, you'll have your own game logic)
    //     if (false /* replace with actual game over condition */) {
    //         isGameOver = true;
    //     }
    // }

    return 0;
}

