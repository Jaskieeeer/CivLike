#ifndef TOWN_H
#define TOWN_H

#include <vector>
#include "Building.h"
#include "Unit.h"
#include <string>
#include <queue>
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
    int health;
    std::queue<std::pair<std::string, int>> unitQueue;  
    std::queue<std::pair<Building, int>> buildingQueue;  
    
public:
    Town(int x, int y, Player* owner);
    Player* getOwner() const;
    int getX() const;
    int getY() const;
    int getHealth() const;
    void setOwner(Player* player);
    bool addBuilding(const Building& building,int turns);
    void getActions();
    void getBuildingActions();
    void getUnitActions();
    void defend(int damage, Player* attacker);
    std::vector<Building> getBuildings();
    std::pair<int, int> getSpawnCoordinates() const;
    void displayTownStatus(); 
    int getIncome() const; 
    int getTownId() const;  
    void buildBuilding(const Building& building); 
    std::string spawnUnit(std::string unitType, Player * player);  
    void update();  
};

#endif 
