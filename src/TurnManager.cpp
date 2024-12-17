#include "../include/TurnManager.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>
#include "../include/Player.h"
#include "../include/Globals.h"
#include "../include/Settler.h"

TurnManager::TurnManager(Player* p1, Player* p2)
: player1(p1), player2(p2), currentPlayer(1), isTurnSkipped(false) {
    currentTurn = 1;
    alternator = 0;
}


void TurnManager::skipTurn() {
    isTurnSkipped = true;  // Set flag to skip the turn
}

Player& TurnManager::getCurrentPlayer() const {
    if (currentPlayer == 1) {
        return *player1;
    } else {
        return *player2;
    }
}
Player& TurnManager::getOpponentPlayer() const {
    if (currentPlayer == 1) {
        return *player2;
    } else {
        return *player1;
    }
}


void TurnManager::nextTurn() {
    currentTurn++;
    for (const auto &unit : getCurrentPlayer().getUnits()) {
        unit->resetTurn();
    }
    for (const auto &unit : getOpponentPlayer().getUnits()) {
        unit->resetTurn();
    }
    getCurrentPlayer().updateGold();
    getOpponentPlayer().updateGold();
}


void TurnManager::nextPlayer() {
    if (alternator == 0){
        alternator++;
    }else{
        alternator = 0;
        nextTurn();

    }
    
    
    if (isTurnSkipped) {
        if (currentPlayer == 1) {
            currentPlayer = 2;
        } else {
            currentPlayer = 1;
        }
        isTurnSkipped = false;  // Reset the skip flag
    } else {
        if (currentPlayer == 1) {
            currentPlayer = 2;
        } else {
            currentPlayer = 1;
        }
    }

}

std::string TurnManager::performAction(std::string input, Unit *unit) {
    std::string message = "";
    if (input == "s"){
        return "skip";
    }
    else if(input== "m")
    {
        
        int x,y;
        int _ = 0;
        while (true) {
            if (_!=0){
            std::cout << "Enter target x and y (or 's' to skip): ";
            }
            std::getline(std::cin, input); 

            if (input == "s") {
                return "skip";
            }
            std::istringstream iss(input);
            if (iss >> x >> y) { 
                break; 
            } else if( _!=0) {
                std::cout <<"Invalid input. Please enter two integers or 's' to stop.\n";
            }
            if (_ == 0){
                _++;
            }
        }
    

        if (unit) {
            if (globalGrid.moveUnit(unit->getX(), unit->getY(), x, y)) {
                unit->move(x - unit->getX(), y - unit->getY());
            } else {
                message+= "Invalid move!\n";
            }
        } 

    }
    else if(input== "a"){
        int x,y;
        std::cout<<"Enter target location: ";
        std::cin>>x>>y;
        if (std::find(unitTypes.begin(), unitTypes.end(), globalGrid.getCellType(x, y)) != unitTypes.end()) {
            int defenderId = globalGrid.getUnitId(x, y);
            Unit* attacker = unit;
            Unit* defender = getOpponentPlayer().getUnit(defenderId);
            if (attacker && defender) {

                message += attacker->attack(*defender);
                getCurrentPlayer().cleanupUnits(); 
                getOpponentPlayer().cleanupUnits();
            } else {
                message +=  "defender not found! \n";
            }
        }else if(globalGrid.getCellType(x, y) == Cell::Type::TOWN){
            message += "attack a town! \n";
        }else{
            message += "Invalid target! \n";
        }
    }
    else if(input== "t"){
        if (unit->isSettler()) {
            Settler* settler = dynamic_cast<Settler*>(unit);
            settler->transformIntoTown(&getCurrentPlayer());
            message += "Transformed into town! \n";
        } else {
            message += "Invalid action! \n";
        }
    }
    else {
        // Handle other cases if needed
    }
    return message;
}

std::string TurnManager::performAction(std::string input, Town *town) {
    std::string message = "";
    if (input == "s"){
        return "skip";
    }
    else if(input== "b"){
        std::string buildingType;
        std::cout<<"Enter building type :\n-Barracks(b)\n-Farm(f)\n-Market(m)\n";
        std::cin>>buildingType;
        if (buildingType == "b") {
            town->addBuilding(Building(Building::Type::Barracks));
            message += "Built a Barracks! \n";
        } else if (buildingType == "f") {
            town->addBuilding(Building(Building::Type::Farm));
            message += "Built a Farm! \n";
        } else if (buildingType == "m") {
            town->addBuilding(Building(Building::Type::Market));
            message += "Built a Market! \n";
        } else {
            message += "Invalid building type! \n";
        }
    }
    else if(input== "u"){
        std::string unitType;
        std::cout<<"Enter unit type:\n-Settler(s)\n-Warrior(w)\n";
        std::cin>>unitType;
        town->spawnUnit(unitType, &getCurrentPlayer());
    }
    else {
        // Handle other cases if needed
    }
    return message;
}


int TurnManager::getCurrentTurn() const {
    return currentTurn;
}

void TurnManager::displayStatus() {
    globalGrid.displayAsciiArt(getCurrentPlayer().getPositions());
    std::cout << "Current player: " << currentPlayer << " Current turn: "<< currentTurn << std::endl;
    getCurrentPlayer().displayInfo();   
    getCurrentPlayer().displayUnitStatus();
    getCurrentPlayer().displayTownStatus();
}
