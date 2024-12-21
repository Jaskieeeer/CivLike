#ifndef WARRIOR_H
#define WARRIOR_H

#include "Unit.h"
#include "Player.h"

class Warrior : public Unit {

public:
    Warrior( int x, int y, Player* player); 
    int getHealth() const override { return 250; }  
    int getAttack() const override { return 80; }
    int getDefense() const override { return 25; }
    int getMovementSpeed() const override { return 5; }
    void displayStatus() const override;  
    bool isWarrior() const override ; 
    int getCost() const override { return 100; } 
    
};

#endif 
