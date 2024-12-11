#include "../include/Town.h"
#include "../include/Player.h"
#include "../include/Settler.h"
#include <iostream>
#include <string>
int Town::townIdCounter = 0;

Town::Town(int x, int y, Player *player) : x(x), y(y), owner(player) {
    townID = ++townIdCounter;
}

void Town::addBuilding(const Building& building) {
    buildings.push_back(building);
}



void Town::produceResources() {
    // Resource production logic can be based on buildings in the town
    for (auto& building : buildings) {
        building.effect();
    }
}

void Town::displayTownStatus() {
    std::cout << "Town at (" << x << ", " << y << ") has " << buildings.size() 
              << " buildings and " << garrison.size() << " units garrisoned." << std::endl;
}

Player* Town::getOwner() const {
    return owner;
}

int Town::getX() const {
    return x;
}

int Town::getY() const {
    return y;
}

void Town::setOwner(Player* player) {
    owner = player;
}

int Town::getTownId() const {
    return townID;
}

void Town::spawnUnit(std::string unitType , Player* player) {
    std::cout << "Town " << townID << " is spawning a unit!" << std::endl;
    if(unitType == "Settler"){
        player->addUnit(new Settler( x, y,player)); //create a new settler 
    }
    // else if(unitType == "Warrior"){
    //     trainUnit(new Warrior(100, 20, 10, x, y));
    // }
    // else if(unitType == "Archer"){
    //     trainUnit(new Archer(100, 15, 5, x, y));
    // }
    else{
        std::cout << "Invalid unit type!" << std::endl;
    }

}