


#ifndef SETTLER_H
#define SETTLER_H

#include "Unit.h"
#include "Town.h"
#include "Player.h"
#include <vector>
#include <string>

class Settler : public Unit {

public:
    Settler( int x, int y, Player* player); // Constructor for the settler
    int getHealth() const override { return 100; }  
    int getAttack() const override { return 10; }
    int getDefense() const override { return 5; }
    int getMovementSpeed() const override { return 3; }
    void transformIntoTown(Player* player); // Method to transform the settler into a town
    void displayStatus() const override;  
    std::vector<std::string> getActions() const override; // Override the base class method to add the transform action
    bool isSettler() const override; // Override the base class method to indicate this is a settler
    bool isWarrior() const override; // Override the base class method to indicate this is not a warrior

    
};

#endif // SETTLER_H
