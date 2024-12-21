#include "../include/Player.h"
#include <iostream>
#include <algorithm>
#include "../include/Settler.h"
#include "../include/Grid.h"
#include "../include/Globals.h"
#include "../include/Gold.h"
int Player::playerIdCounter = 0;
Player::Player(std::string name, Civilization* civ)
    : name(name), civilization(civ), gold(Gold<int>(civ->getStartingGold())), goldIncome(0) {
    playerID = ++playerIdCounter;
    
    }

Player::~Player() {
    for (Unit* unit : units) {
        delete unit;
    }
    units.clear();

    for (Town* town : towns) {
        delete town;
    }
    towns.clear();

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
bool Player::hasSettlersOrTowns() {
    for (Unit* unit : units) {
        Settler* settler = dynamic_cast<Settler*>(unit);
        if (settler != nullptr) {
            return true;
        }
    }
    return !towns.empty();
}
void Player::transformUnitIntoTown(int unitID) {
    Unit* unit = getUnit(unitID);
    if (unit != nullptr) {
        Settler* settler = dynamic_cast<Settler*>(unit);
        if (settler != nullptr) {
            settler->transformIntoTown(this);
           
        } else {
            std::cout << "Unit with ID " << unitID << " is not a Settler and cannot transform into a town." << std::endl;
        }
    } else {
        std::cout << "Unit with ID " << unitID << " not found." << std::endl;
    }
}

std::vector<std::pair<int, int>> Player::getPositions() const {
    std::vector<std::pair<int, int>> positions;
    for (Unit* unit : units) {
        positions.push_back(std::make_pair(unit->getX(), unit->getY()));
    }
    for (Town* town : towns) {
        positions.push_back(std::make_pair(town->getX(), town->getY()));
    }
    return positions;
}

void Player::printPositions() const{
    for (Unit* unit : units) {
        std::cout << "(" << unit->getX() << ", " << unit->getY() << ") ";
    }
    for (Town* town : towns) {
        std::cout << "(" << town->getX() << ", " << town->getY() << ") ";
    }
    std::cout << std::endl;
}

void Player::addTown(Town* town) {
    towns.push_back(town);
    updateIncome();
}

int Player::getGold() const {
    return gold.getGold();
}

void Player::setGold(int amount) {
    gold.setGold(amount);    
}

void Player::loseTown(Town* town, Player* conqueror) {
    towns.erase(std::remove(towns.begin(), towns.end(), town), towns.end());
    if(conqueror!=nullptr){
        conqueror->addTown(town);
        town->setOwner(conqueror);
        globalGrid.setCell(town->getX(), town->getY() , Cell::Type::TOWN, town->getTownId(),conqueror->getPlayerID());
        updateIncome();
    }
}

void Player::updateIncome() {
    goldIncome = 0;
    for (Town* town : towns) {
        goldIncome += town->getIncome();
    }
}

void Player::updateGold() {
    gold.setGold(gold.getGold() + goldIncome);
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



const std::vector<Unit*>& Player::getUnits() const {
    return units;
}

Unit* Player::getUnit(int unitID) const{
    for (Unit* unit : units) {
        if (unit->getId() == unitID) {  
            return unit;
        }
    }
    return nullptr;  
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
    return nullptr; 
}


void Player::displayUnitStatus() const {
    for (Unit* unit : units) {
        unit->displayStatus();
    }
}
void Player::displayTownStatus() const {
    for (Town* town : towns) {
        town->displayTownStatus();
    }
}


void Player::displayInfo() const {
    std::cout << "Player: " << name << "\n";
    std::cout << "Gold: " << gold.getGold() << "\n";
    std::cout << "Towns: " << towns.size() << "\n";
    std::cout << "Units: " << units.size() << "\n";
    if (civilization) {
        std::cout << "Civilization: " << civilization->getName() << "\n";
    } else {
        std::cout << "Civilization pointer is null!\n";
    }
}
