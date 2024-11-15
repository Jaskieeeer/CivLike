#include "../include/Settler.h"
#include "../include/Town.h"
#include "../include/Grid.h"
#include "../include/Globals.h"
#include <iostream>

Settler::Settler(int x, int y)
    : Unit(x, y) {
        health=100;
        attackPower=10;
        defense=5;
        movementSpeed=2;
    }

void Settler::transformIntoTown(Player* player) {
    if (globalGrid.canSpawnTown(x,y)) {
        Town* newTown = new Town(getX(), getY(), player);  // Dynamically allocate a new Town
        player->addTown(newTown);  // Add the new town to the player's town list
        globalGrid.setCell(x, y, Cell::Type::TOWN, newTown->getTownId());  // Update the grid
        player->removeUnit(getId());  // Remove the settler from the player's unit list

    }else{
        std::cout << "Cannot spawn town here!" << std::endl;
    }
    
}


bool Settler::isSettler() const {
    return true; // This is a Settler
}
