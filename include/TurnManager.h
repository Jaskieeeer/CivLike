#ifndef TURNMANAGER_H
#define TURNMANAGER_H

class TurnManager {
private:
    int currentPlayer;    // Current player (1 or 2)
    bool isTurnSkipped;   // Flag to indicate if the turn should be skipped

public:
    TurnManager();        // Constructor to initialize state
    void skipTurn();      // Method to skip the current player's turn
    int getCurrentPlayer() const;  // Method to get the current player
    void nextTurn();      // Method to switch to the next player, possibly skipping
};

#endif // TURNMANAGER_H
