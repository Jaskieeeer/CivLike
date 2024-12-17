#ifndef TOWN_H
#define TOWN_H

#include <vector>
#include "Building.h"
#include "Unit.h"
#include <string>
#include <utility>

class Player;  // Forward declaration

class Town {
private:
    static int townIdCounter;  // Static counter for generating unique IDs
    int townID;          // Unique ID for the player  
    int x, y;  // Coordinates on the grid
    std::vector<Building> buildings;
    Player* owner;  // Pointer to the player who owns the town
    int income;
public:
    Town(int x, int y, Player* owner);
    Player* getOwner() const;
    int getX() const;
    int getY() const;
    void setOwner(Player* player);
    void addBuilding(const Building& building);
    void getActions();
    void getBuildingActions();
    void getUnitActions();
    std::vector<Building> getBuildings();
    std::pair<int, int> getSpawnCoordinates() const;
    void displayTownStatus(); // For debugging or displaying town details
    int getIncome() const;  // Getter for income
    int getTownId() const;  // Getter for town ID
    void spawnUnit(std::string unitType, Player * player);  // Spawn a unit
};

#endif // TOWN_H
