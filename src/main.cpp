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
#include "../include/Warrior.h"
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
    std::cout<<globalGrid.getWidth();
    
    
    Player player1("Alice", new RomanCiv());
    Player player2("Bob", new RomanCiv());
    TurnManager turnManager(&player1, &player2);
    std::vector<std::pair<int, int>> spawnPoints = generateSpawnPoints(2, globalGrid.getWidth(), globalGrid.getHeight());
    player1.addUnit(new Settler (spawnPoints[0].first, spawnPoints[0].second,&player1));
    player2.addUnit(new Settler (spawnPoints[1].first, spawnPoints[1].second,&player2)); 
    bool isGameOver = false;

    globalGrid.displayAsciiArt(player1.getPositions());
    player1.transformUnitIntoTown(1);
    globalGrid.displayAsciiArt(player1.getPositions());
    player1.loseTown(player1.getTown(1),&player2);
    globalGrid.displayAsciiArt(player1.getPositions());
     

    player1.addUnit(new Settler ( 5,5,&player1));
    player2.addUnit(new Warrior ( 4,4,&player2));
    globalGrid.displayAsciiArt(player1.getPositions());

    Unit* attacker = player2.getUnit(globalGrid.getUnitId(4,4));
    Unit* defender = player1.getUnit(globalGrid.getUnitId(5,5));
    attacker->attack(*defender);
    attacker->resetTurn();
    attacker->attack(*defender);
    player1.cleanupUnits();  // Clean up dead units
    player2.cleanupUnits();  // Clean up dead units
    player1.displayInfo();
    player2.displayInfo();
    globalGrid.displayAsciiArt(player2.getPositions());
    globalGrid.displayAsciiArt(player1.getPositions());
    std::cout << "Player 1's units: " << player1.getUnits().size() << std::endl;    

    player1.addUnit(new Settler ( 5,7,&player1));
    player1.displayInfo();
    globalGrid.displayAsciiArt(player1.getPositions());
    player2.displayInfo();
    for (const auto& pos : player2.getPositions()) {
        std::cout << "(" << pos.first << ", " << pos.second << ") ";
    }

    std::cout << std::endl;
    globalGrid.displayAsciiArt(player2.getPositions());

     
    std::string message = "";
    // game loop
    while (!isGameOver) {
        if (!turnManager.getCurrentPlayer().hasSettlersOrTowns()) {
            isGameOver = true;
            std::cout << "Player " << turnManager.getOpponentPlayer().getPlayerID() << " wins!\n";
            break;
        }
        std::cout << "Player " << turnManager.getCurrentPlayer().getPlayerID() << "'s turn\n";
        bool isTurnSkipped = false;
        while(!isTurnSkipped){
            for (int i = 0; i < 100; ++i) std::cout << "\n";  // Clear the console
            std::cout<<"info: \n"<<message<<std::endl;
            message = "";
            turnManager.displayStatus();
            std::cout << "Player " << turnManager.getCurrentPlayer().getPlayerID() << " is taking action...\n";

            std::cout << "Possible actions: \n - move\n - attack\n - skip turn (s)\n - give up (ff)\n";
            std::string input;
            std::cin >> input;
            if (input == "s") 
            {
                turnManager.skipTurn();
                isTurnSkipped = true;
            } 
            else if (input == "ff") 
            {
                isGameOver = true;
                std::cout << "Player " << turnManager.getOpponentPlayer().getPlayerID() << " wins!\n";
                break;
            } 
            else 
            {
                message = turnManager.performAction(input);
            }
            
        }

        turnManager.nextTurn();
    }
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

