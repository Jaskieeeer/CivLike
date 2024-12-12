#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include "Player.h"
class TurnManager {
private:
    const Player *player1; 
    const Player *player2; 

    int currentPlayer;    // Current player (1 or 2)
    bool isTurnSkipped;   // Flag to indicate if the turn should be skipped

public:
    TurnManager(const Player* p1, const Player* p2);        // Constructor to initialize state
    Player getCurrentPlayer() const;  // Method to get a player by ID
    Player getOpponentPlayer() const;
    void skipTurn();      // Method to skip the current player's turn
    void nextTurn();      // Method to switch to the next player, possibly skipping
    void displayStatus();
    std::string performAction(std::string input);
};

#endif // TURNMANAGER_H
