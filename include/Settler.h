


#ifndef SETTLER_H
#define SETTLER_H

#include "Unit.h"
#include "Town.h"
#include "Player.h"

class Settler : public Unit {
private:
    bool hasTurnedIntoTown; // Flag to check if the settler has turned into a town
    int movementSpeed; // Movement speed of the settler
public:
    Settler(int health, int attackPower, int defense, int x, int y);

    void transformIntoTown(Player& player); // Method to transform the settler into a town
    bool isSettler() const; // Override the base class method to indicate this is a settler
    
};

#endif // SETTLER_H
