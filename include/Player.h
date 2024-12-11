#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Unit.h"
#include "Town.h"
#include "Building.h"
#include "Civilization.h"


class Player {
private:
    static int playerIdCounter;  // Static counter for generating unique IDs
    int playerID;          // Unique ID for the player
    std::unordered_map<std::string, int> resources; // Stores resources such as gold, wood, etc.
    std::string name;      // Player's name
    Civilization* civilization;  // Pointer to the player's civilization
    std::vector<Unit*> units;    // List of pointers to units controlled by the player
    std::vector<Town*> towns;    // List of pointers to towns controlled by the player
    int gold;               // Example resource type, initially set to 0
public:
    

    // Constructor to initialize the player with a name and a reference to their civilization
    Player(std::string name, Civilization* civ);

    // Player methods

    void addUnit(Unit* unit);  // Add a unit to the player's list
    void removeUnit(int unitId);  // Remove a unit from the player's list


    void transformUnitIntoTown(int unitID);  // Transform a settler unit into a town


    void addTown(Town* town);  // Add a town to the player's list
    void loseTown(Town* town,Player* player = nullptr);  // Remove a town from the player's list

    void addResource(std::string resourceName, int amount);  // Add resource to the player's stock
    void spendResource(std::string resourceName, int amount);   // Spend resources (decrease stock)
 


    // Getters

    int getPlayerID() const;
    const std::string& getName() const;
    Civilization* getCivilization() const;
    const std::unordered_map<std::string, int>& getResources() const;
    const std::vector<Unit*>& getUnits() const;
    Unit* getUnit(int unitID) const;
    const std::vector<Town*>& getTowns() const;
    Town* getTown(int townID) const;

    void displayInfo() const;


};

#endif // PLAYER_H
