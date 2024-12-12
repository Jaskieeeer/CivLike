#include "../include/Player.h"
#include <iostream>
#include <algorithm>
#include "../include/Settler.h"
#include "../include/Grid.h"
#include "../include/Globals.h"
int Player::playerIdCounter = 0;
Player::Player(std::string name, Civilization* civ)
    : name(name), civilization(civ), gold(civ->getStartingGold()) {
    playerID = ++playerIdCounter;
    }

void Player::addUnit(Unit* unit) {
    
    units.push_back(unit);
}

void Player::removeUnit(int unitId) {
    for (auto it = units.begin(); it != units.end(); ++it) {
        if ((*it)->getId() == unitId) {
            delete *it;
            units.erase(it);
            break;
        }
    }
}

void Player::cleanupUnits() {
    for (auto it = units.begin(); it != units.end();) {
        if ((*it)->isMarkedForDeletion()) {
            delete *it;
            it = units.erase(it);
        } else {
            ++it;
        }
    }
}

void Player::transformUnitIntoTown(int unitID) {
    // Get the unit by ID
    Unit* unit = getUnit(unitID);
    if (unit != nullptr) {
        // Try to cast the Unit pointer to a Settler pointer
        Settler* settler = dynamic_cast<Settler*>(unit);
        if (settler != nullptr) {
            // If successful, call transformIntoTown
            settler->transformIntoTown(this);
           
        } else {
            // The unit exists, but is not a Settler
            std::cout << "Unit with ID " << unitID << " is not a Settler and cannot transform into a town." << std::endl;
        }
    } else {
        // The unit was not found
        std::cout << "Unit with ID " << unitID << " not found." << std::endl;
    }
}

void Player::addTown(Town* town) {
    towns.push_back(town);
}

void Player::loseTown(Town* town, Player* conqueror) {
    towns.erase(std::remove(towns.begin(), towns.end(), town), towns.end());
    if(conqueror!=nullptr){
        conqueror->addTown(town);
        town->setOwner(conqueror);
        globalGrid.setCell(town->getX(), town->getY() , Cell::Type::TOWN, town->getTownId(),conqueror->getPlayerID());
    }
}

void Player::addResource(std::string resourceName, int amount) {
    resources[resourceName] += amount;
}

void Player::spendResource(std::string resourceName, int amount) {
    if (resources[resourceName] < amount) {
        std::cout << "Insufficient " << resourceName << " to spend " << amount << std::endl;
        return;
    }
    resources[resourceName] -= amount;
}

int Player::getPlayerID() const {
    return playerID;
}

const std::string& Player::getName() const {
    return name;
}

Civilization* Player::getCivilization() const {
    return civilization;
}

const std::unordered_map<std::string, int>& Player::getResources() const {
    return resources;
}

const std::vector<Unit*>& Player::getUnits() const {
    return units;
}

Unit* Player::getUnit(int unitID) const{
    for (Unit* unit : units) {
        if (unit->getId() == unitID) {  // Assuming Unit has a getID() method
            return unit;
        }
    }
    return nullptr;  // Return nullptr if unit with the given ID is not found
}



const std::vector<Town*>& Player::getTowns() const {
    return towns;
}

Town* Player::getTown(int townID) const {
    for (Town* town : towns) {
        if (town->getTownId() == townID) {
            return town;
        }
    }
    return nullptr;  // Return nullptr if town with the given ID is not found
}





void Player::displayInfo() const {
    std::cout << "Player: " << name << "\n";
    std::cout << "Gold: " << gold << "\n";
    std::cout << "Towns: " << towns.size() << "\n";
    std::cout << "Units: " << units.size() << "\n";
    if (civilization) {
        std::cout << "Civilization: " << civilization->getName() << "\n";
    } else {
        std::cout << "Civilization pointer is null!\n";
    }
}
