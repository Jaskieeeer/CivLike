#ifndef TOWN_H
#define TOWN_H

#include <vector>
#include "Building.h"
#include "Unit.h"

class Player;  // Forward declaration

class Town {
private:
    static int townIdCounter;  // Static counter for generating unique IDs
    int townID;          // Unique ID for the player  
    int x, y;  // Coordinates on the grid
    std::vector<Building> buildings;
    std::vector<Unit*> garrison; // Units stationed in the town
    Player* owner;  // Pointer to the player who owns the town
public:
    Town(int x, int y, Player* owner);
    Player* getOwner() const;
    void setOwner(Player* player);
    void addBuilding(const Building& building);
    void trainUnit(Unit* unit);  // Add unit to the garrison
    void produceResources();
    void displayTownStatus(); // For debugging or displaying town details
};

#endif // TOWN_H
