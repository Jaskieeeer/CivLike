#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include "Player.h"
class TurnManager {
private:
    Player *player1; 
    Player *player2; 
    int currentTurn;      // Current turn number
    int alternator;
    int currentPlayer;    // Current player (1 or 2)
    bool isTurnSkipped;   // Flag to indicate if the turn should be skipped

public:
    TurnManager(Player* p1, Player* p2);        // Constructor to initialize state
    Player& getCurrentPlayer() const;  // Method to get a player by ID
    Player& getOpponentPlayer() const;
    int getCurrentTurn() const;     // Method to get the current turn number
    void skipTurn();      // Method to skip the current player's turn
    void nextTurn();      // Method to switch to the next player, possibly skipping
    void nextPlayer();
    void displayStatus();
    std::string performAction(std::string input, Unit *unit);
    std::string performAction(std::string input, Town *town);

};

#endif // TURNMANAGER_H
