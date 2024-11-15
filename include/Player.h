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

public:
    std::string name;      // Player's name
    Civilization* civilization;  // Pointer to the player's civilization
    std::vector<Unit*> units;    // List of pointers to units controlled by the player
    std::vector<Town*> towns;    // List of pointers to towns controlled by the player
    int gold;               // Example resource type, initially set to 0

    // Constructor to initialize the player with a name and a reference to their civilization
    Player(std::string name, Civilization* civ);

    // Player methods
    void addUnit(Unit* unit);  // Add a unit to the player's list
    void addTown(Town* town);  // Add a town to the player's list
    void addResource(std::string resourceName, int amount);  // Add resource to the player's stock
    void gatherResource(std::string resourceName, int amount);  // Gather resources (add to stock)
    void spendResource(std::string resourceName, int amount);   // Spend resources (decrease stock)
    void removeUnit(int unitId);  // Remove a unit from the player's list
    void loseTown(Town* town,Player* player = nullptr);  // Remove a town from the player's list
    // Display information about the player
    void displayInfo() const;

    // Getter for Player ID
    int getPlayerID() const;
};

#endif // PLAYER_H
