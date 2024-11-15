#include "../include/Player.h"
#include <iostream>
#include <algorithm>
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
