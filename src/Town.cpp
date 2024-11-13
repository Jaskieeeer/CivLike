#include "../include/Town.h"
#include <iostream>

Town::Town(int x, int y) : x(x), y(y) {}

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
