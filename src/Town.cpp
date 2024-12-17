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

Town::Town(int x, int y, Player *player) : x(x), y(y), owner(player),income(100) {
    townID = ++townIdCounter;
}

void Town::addBuilding(const Building& building) {
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
    std::cout << "Build: Settler(s)" << std::endl;
    for(auto building : buildings){
        if(building.getType() == Building::Type::Barracks){
            std::cout << "Build: Warrior(w)" << std::endl;
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
void Town::spawnUnit(std::string unitType , Player* player) {
    int spawnX, spawnY;
    std::tie(spawnX, spawnY) = getSpawnCoordinates();
    if(unitType == "s"){
        player->addUnit(new Settler(spawnX,spawnY,player)); 
    }
    else if(unitType == "w"){
        if (std::find_if(buildings.begin(), buildings.end(), [](const Building& building) {
            return building.getType() == Building::Type::Barracks;
        }) == buildings.end()) {
            std::cout << "Barracks not found! Cannot build a warrior." << std::endl;
            return;
        }
        player->addUnit(new Warrior(spawnX,spawnY,player));
    }
    
    else{
        std::cout << "Invalid unit type!" << std::endl;
    }

}