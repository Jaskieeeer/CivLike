#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include "Player.h"
class TurnManager {
private:
    Player *player1; 
    Player *player2; 
    int currentTurn;      
    int alternator;
    int currentPlayer;   
    bool isTurnSkipped;   

public:
    TurnManager(Player* p1, Player* p2);
    ~TurnManager();        
    Player& getCurrentPlayer() const; 
    Player& getOpponentPlayer() const;
    int getCurrentTurn() const;    
    void skipTurn();     
    void nextTurn();     
    void nextPlayer();
    void displayStatus();
    std::string performAction(std::string input, Unit *unit);
    std::string performAction(std::string input, Town *town);

};

#endif 