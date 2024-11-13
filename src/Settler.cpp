#include "../include/Settler.h"
#include "../include/Town.h"

Settler::Settler(int health, int attackPower, int defense, int x, int y)
    : Unit( health, attackPower,defense, x, y) {}

void Settler::transformIntoTown(Player& player) {
    Town* newTown = new Town(getX(), getY());  // Dynamically allocate a new Town
    player.addTown(newTown);  // Add the new town to the player's town list

    // TODO: Remove the settler from the player's list of units
}


bool Settler::isSettler() const {
    return true; // This is a Settler
}
