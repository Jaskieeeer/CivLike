#include "../include/Player.h"
#include <iostream>
#include <algorithm>
#include "../include/Settler.h"
int Player::playerIdCounter = 0;
Player::Player(std::string name, Civilization* civ)
    : name(name), civilization(civ), gold(civ->getStartingGold()) {
    playerID = ++playerIdCounter;
    }

void Player::addUnit(Unit* unit) {
    units.push_back(unit);
}

void Player::addTown(Town* town) {
    towns.push_back(town);
}
void Player::loseTown(Town* town, Player* conqueror) {
    towns.erase(std::remove(towns.begin(), towns.end(), town), towns.end());
    town->setOwner(conqueror);  // Transfer ownership to the conqueror
    conqueror->addTown(town);  // Add the town to the conqueror's list
}

void Player::removeUnit(int unitId) {
    for (auto it = units.begin(); it != units.end(); ++it) {
        if ((*it)->getId() == unitId) {
            units.erase(it);
            break;
        }
    }
}

Unit* Player::getUnit(int unitID) {
    for (Unit* unit : units) {
        if (unit->getId() == unitID) {  // Assuming Unit has a getID() method
            return unit;
        }
    }
    return nullptr;  // Return nullptr if unit with the given ID is not found
}

Town* Player::getTown(int townID) {
    for (Town* town : towns) {
        if (town->getTownId() == townID) {
            return town;
        }
    }
    return nullptr;  // Return nullptr if town with the given ID is not found
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
