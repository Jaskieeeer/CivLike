


#ifndef SETTLER_H
#define SETTLER_H

#include "Unit.h"
#include "Town.h"
#include "Player.h"

class Settler : public Unit {

public:
    Settler( int x, int y, Player* player); // Constructor for the settler
    int getHealth() const override { return 100; }  
    int getAttack() const override { return 10; }
    int getDefense() const override { return 5; }
    int getMovementSpeed() const override { return 2; }
    void transformIntoTown(Player* player); // Method to transform the settler into a town
    bool isSettler() const; // Override the base class method to indicate this is a settler
    

    
};

#endif // SETTLER_H
