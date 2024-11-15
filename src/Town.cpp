#include "../include/Town.h"
#include "../include/Player.h"
#include <iostream>

int Town::townIdCounter = 0;

Town::Town(int x, int y, Player *player) : x(x), y(y), owner(player) {
    townID = ++townIdCounter;
}

void Town::addBuilding(const Building& building) {
    buildings.push_back(building);
}

void Town::trainUnit(Unit* unit) {
    garrison.push_back(unit);
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

void Town::setOwner(Player* player) {
    owner = player;
}