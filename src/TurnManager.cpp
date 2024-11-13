#include "../include/TurnManager.h"

TurnManager::TurnManager() : currentPlayer(1), isTurnSkipped(false) {}

void TurnManager::skipTurn() {
    isTurnSkipped = true;  // Set flag to skip the turn
}

int TurnManager::getCurrentPlayer() const {
    return currentPlayer;
}

void TurnManager::nextTurn() {
    if (isTurnSkipped) {
        // If the turn is skipped, switch to the next player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        isTurnSkipped = false;  // Reset the skip flag
    } else {
        // Switch to the next player normally
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}
