


#ifndef SETTLER_H
#define SETTLER_H

#include "Unit.h"
#include "Town.h"
#include "Player.h"
#include <vector>
#include <string>

class Settler : public Unit {

public:
    Settler( int x, int y, Player* player); 
    int getHealth() const override { return 100; }  
    int getAttack() const override { return 10; }
    int getDefense() const override { return 5; }
    int getMovementSpeed() const override { return 3; }
    void transformIntoTown(Player* player);
    void displayStatus() const override;  
    std::vector<std::string> getActions() const override; 
    bool isSettler() const override;
    bool isWarrior() const override; 
    int getCost() const override { return 50; } 
    
};

#endif 
