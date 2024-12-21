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
        usedMovementSpeed = movementSpeed;
        didAttack = true;
    }

std::vector<std::string> Settler::getActions() const {
    std::vector<std::string> actions = Unit::getActions();
    actions.push_back("Transform into town(t)");
    return actions;
}

void Settler::transformIntoTown(Player* player) {
    if (globalGrid.canSpawnTown(x,y)) {
        Town* newTown = new Town(getX(), getY(), player);  
        player->addTown(newTown);  
        globalGrid.setCell(x, y, Cell::Type::TOWN, newTown->getTownId(),player->getPlayerID());  
        player->removeUnit(getId());  
    }else{
        std::cout << "Cannot spawn town here!" << std::endl;
    }
    
}

void Settler::displayStatus() const {
    std::cout << "Settler unit " << id << " at (" << x << ", " << y << ") with health " << health << ". Movement speed left: "<< movementSpeed-usedMovementSpeed<<std::endl;
}


bool Settler::isSettler() const {
    return true; 
}

bool Settler::isWarrior() const {
    return false;
}