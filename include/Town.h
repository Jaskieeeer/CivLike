#ifndef TOWN_H
#define TOWN_H

#include <vector>
#include "Building.h"
#include "Unit.h"

class Town {
private:
    int x, y;  // Coordinates on the grid
    std::vector<Building> buildings;
    std::vector<Unit*> garrison; // Units stationed in the town

public:
    Town(int x, int y);
    void addBuilding(const Building& building);
    void trainUnit(Unit* unit);  // Add unit to the garrison
    void produceResources();
    void displayTownStatus(); // For debugging or displaying town details
};

#endif // TOWN_H
