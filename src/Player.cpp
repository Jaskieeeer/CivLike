#include "../include/Player.h"
#include <iostream>

Player::Player(std::string name, Civilization* civ)
    : name(name), civilization(civ), gold(civ->getStartingGold()) {
         std::cout << "Initialized Player with Civilization: " << civilization->getName() 
              << ", Starting Gold: " << gold << "\n";
    }

void Player::addUnit(Unit* unit) {
    units.push_back(unit);
}

void Player::addTown(Town* town) {
    towns.push_back(town);
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
