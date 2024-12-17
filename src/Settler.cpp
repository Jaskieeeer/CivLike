#include "../include/Settler.h"
#include "../include/Town.h"
#include "../include/Grid.h"
#include "../include/Globals.h"
#include <iostream>

Settler::Settler(int x, int y, Player* player)
    : Unit(x, y, player) {
        globalGrid.setCell(x, y, Cell::Type::SETTLER, id,player->getPlayerID());
        health=100;
        attackPower=10;
        defense=5;
        movementSpeed=3;
    }

std::vector<std::string> Settler::getActions() const {
    std::vector<std::string> actions = Unit::getActions();
    actions.push_back("Transform into town(t)");
    return actions;
}

void Settler::transformIntoTown(Player* player) {
    if (globalGrid.canSpawnTown(x,y)) {
        Town* newTown = new Town(getX(), getY(), player);  // Dynamically allocate a new Town
        player->addTown(newTown);  // Add the new town to the player's town list
        globalGrid.setCell(x, y, Cell::Type::TOWN, newTown->getTownId(),player->getPlayerID());  // Update the grid
        player->removeUnit(getId());  // Remove the settler from the player's unit list

    }else{
        std::cout << "Cannot spawn town here!" << std::endl;
    }
    
}

void Settler::displayStatus() const {
    std::cout << "Settler unit " << id << " at (" << x << ", " << y << ") with health " << health << ". Movement speed left: "<< movementSpeed-usedMovementSpeed<<std::endl;
}


bool Settler::isSettler() const {
    return true; // This is a Settler
}

bool Settler::isWarrior() const {
    return false; // This is not a Warrior
}