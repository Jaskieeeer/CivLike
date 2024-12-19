#include "../include/Town.h"
#include "../include/Player.h"
#include "../include/Settler.h"
#include "../include/Building.h"
#include "../include/Warrior.h"
#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>
#include <Globals.h>
int Town::townIdCounter = 0;

Town::Town(int x, int y, Player *player) : x(x), y(y), owner(player),income(100),health(500) {
    townID = ++townIdCounter;
}

bool Town::addBuilding(const Building& building,int turns) {
    if(owner->getGold() >= building.getCost() && std::find_if(buildings.begin(), buildings.end(), [building](const Building& b) {
        return b.getType() == building.getType();
    }) == buildings.end()) {
        owner->setGold(owner->getGold() - building.getCost());
    }
    else{
        return false;
    }
    buildingQueue.push(std::make_pair(building, turns));

    return true;
}

void Town::buildBuilding(const Building& building) {
    buildings.push_back(building);
    income += building.getIncome();
    owner->updateIncome();
}
void Town::getActions(){
    std::cout<<"Town actions: \n";
    std::cout<<"Skip(s)\n";
    std::cout<<"Previous(p)\n";
    std::cout<<"Build a building(b)\n";
    std::cout<<"Build a unit(u)\n";
    
}
void Town::defend(int damage, Player* attacker) {
    health -= damage;
    if (health <= 0) {
        owner->loseTown(this,attacker);
    }
}
void Town::getBuildingActions() {
    for (Building::Type type: {Building::Type::Barracks, Building::Type::Farm, Building::Type::Market}) {
        if(std::find_if(buildings.begin(), buildings.end(), [type](const Building& building) {
            return building.getType() == type;
        }) == buildings.end()) {
            std::cout << "Build: " << Building::buildingTypeToString(type) << std::endl;
        }
    }
}

void Town::getUnitActions() {
    std::cout << "Build: Settler(s) - 50g" << std::endl;
    for(auto building : buildings){
        if(building.getType() == Building::Type::Barracks){
            std::cout << "Build: Warrior(w) - 150g" << std::endl;
        }
    }
}

std::vector<Building> Town::getBuildings() {
    return buildings;
}



void Town::displayTownStatus() {
    std::cout << "Town at (" << x << ", " << y << ") has " << buildings.size() 
              << " buildings\n";
    if (buildings.size() > 0) {
        std::cout << "Including: " << std::endl;
    
    for (const Building& building : buildings) {
        std::cout << Building::buildingTypeToString(building.getType()) << std::endl;
    }  
    }
    if(unitQueue.size() > 0){
        std::queue<std::pair<std::string, int>> q_copy = unitQueue;
        std::cout << "Units in queue: " << std::endl;
        while (!q_copy.empty()) {
            std::cout << q_copy.front().first << " " << q_copy.front().second <<" turns left"<< std::endl;
            q_copy.pop();
        }
    }
    if(buildingQueue.size() > 0){
        std::queue<std::pair<Building, int>> q_copy = buildingQueue;
        std::cout << "Buildings in queue: " << std::endl;
        while (!q_copy.empty()) {
            std::cout << Building::buildingTypeToString(q_copy.front().first.getType()) << " " << q_copy.front().second <<" turns left"<< std::endl;
            q_copy.pop();
        }
    }
    
    
}

Player* Town::getOwner() const {
    return owner;
}

int Town::getX() const {
    return x;
}

int Town::getY() const {
    return y;
}

int Town::getIncome() const {
    return income;
}

void Town::setOwner(Player* player) {
    owner = player;
}

int Town::getTownId() const {
    return townID;
}

int Town::getHealth() const {
    return health;
}

std::pair<int, int> Town::getSpawnCoordinates() const {
    int gridWidth = globalGrid.getWidth();
    int gridHeight = globalGrid.getHeight();
    int middleX = gridWidth / 2;
    int middleY = gridHeight / 2;

    std::queue<std::pair<int, int>> q;
    std::set<std::pair<int, int>> visited;
    q.push({x, y});
    visited.insert({x, y});

    std::pair<int, int> bestCell = {x, y};
    double bestDistanceToTown = std::numeric_limits<double>::max();
    double bestDistanceToMiddle = std::numeric_limits<double>::max();

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        if (globalGrid.getCellType(cx, cy) == Cell::Type::EMPTY) {
            double distanceToTown = std::sqrt(std::pow(cx - x, 2) + std::pow(cy - y, 2));
            double distanceToMiddle = std::sqrt(std::pow(cx - middleX, 2) + std::pow(cy - middleY, 2));

            if (distanceToTown < bestDistanceToTown || 
                (distanceToTown == bestDistanceToTown && distanceToMiddle < bestDistanceToMiddle)) {
                bestCell = {cx, cy};
                bestDistanceToTown = distanceToTown;
                bestDistanceToMiddle = distanceToMiddle;
            }
        }

        std::vector<std::pair<int, int>> neighbors = {
            {cx + 1, cy}, {cx - 1, cy}, {cx, cy + 1}, {cx, cy - 1}
        };

        for (const auto& [nx, ny] : neighbors) {
            if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight && visited.find({nx, ny}) == visited.end()) {
                q.push({nx, ny});
                visited.insert({nx, ny});
            }
        }
    }

    return bestCell;
}
std::string Town::spawnUnit(std::string unitType , Player* player) {
    if(unitType == "s"){
        if (player->getGold() >= 50) {
            player->setGold(player->getGold() - 50);
        }
        else {
            return "Insufficient funds! \n";
        }
        unitQueue.push(std::make_pair("settler",3));
        return "Added Settler to queue! \n";
    }
    else if(unitType == "w"){
        if (std::find_if(buildings.begin(), buildings.end(), [](const Building& building) {
            return building.getType() == Building::Type::Barracks;
        }) == buildings.end()) {
            return "Barracks not found! \n";
        }
        if (player->getGold() >= 150) {
            player->setGold(player->getGold() - 150);
        }
        else {
            return "Insufficient funds! \n";
        }
        unitQueue.push(std::make_pair("warrior",2));
        return "Added Warrior to queue! \n";

    }
    
    else{
        return "Invalid unit type! \n";
    }

}

void Town::update() {
    if (!buildingQueue.empty()) {
        auto& [building, turns] = buildingQueue.front();
        if (--turns == 0) {
            buildBuilding(building);
            buildingQueue.pop();
        }
    }
    if(!unitQueue.empty()){
        auto& [unitType, turns] = unitQueue.front();
        if(--turns == 0){
            int spawnX, spawnY;
            std::tie(spawnX, spawnY) = getSpawnCoordinates();
            if(unitType == "settler"){
                Settler* settler = new Settler(spawnX,spawnY, owner);
                owner->addUnit(settler);
            }
            else if(unitType == "warrior"){
                Warrior* warrior = new Warrior(spawnX,spawnY, owner);
                owner->addUnit(warrior);
            }
            unitQueue.pop();
        }
    }
}