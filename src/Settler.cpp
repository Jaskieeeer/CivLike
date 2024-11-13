#include "../include/Settler.h"
#include "../include/Town.h"

Settler::Settler(int health, int attackPower, int defense, int x, int y)
    : Unit( health, attackPower,defense, x, y), hasTurnedIntoTown(false) {}

void Settler::transformIntoTown(Player& player) {
    Town newTown( getX(), getY());
    player.addTown(&newTown);  
    //TODO delete settler from player's list of units
    
    
}

bool Settler::isSettler() const {
    return true; // This is a Settler
}
