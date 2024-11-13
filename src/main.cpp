#include <iostream>
#include "../include/Grid.h"
#include "../include/TurnManager.h"
#include "../include/Player.h"
#include "../include/Civilization.h"
#include "../include/RomanCiv.h"
int main() {
    TurnManager turnManager;
    std::cout << "TurnManager created\n";
    Player player1("Alice", new RomanCiv());
    Player player2("Bob", new RomanCiv());
    bool isGameOver = false;
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
