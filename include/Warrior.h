#ifndef WARRIOR_H
#define WARRIOR_H

#include "Unit.h"
#include "Player.h"

class Warrior : public Unit {

public:
    Warrior( int x, int y, Player* player); // Constructor for the settler
    int getHealth() const override { return 250; }  
    int getAttack() const override { return 80; }
    int getDefense() const override { return 25; }
    int getMovementSpeed() const override { return 5; }
    bool isWarrior() const; // Override the base class method to indicate this is a settler
    

    
};

#endif // WARRIOR_H
