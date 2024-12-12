#include "../include/TurnManager.h"
#include <iostream>
#include <vector>
#include "../include/Player.h"
#include "../include/Globals.h"

TurnManager::TurnManager(const Player* p1, const Player* p2)
: player1(p1), player2(p2), currentPlayer(1), isTurnSkipped(false) {}


void TurnManager::skipTurn() {
    isTurnSkipped = true;  // Set flag to skip the turn
}

Player TurnManager::getCurrentPlayer() const {
    if (currentPlayer == 1) {
        return *player1;
    } else {
        return *player2;
    }
}
Player TurnManager::getOpponentPlayer() const {
    if (currentPlayer == 1) {
        return *player2;
    } else {
        return *player1;
    }
}



void TurnManager::nextTurn() {
    for (const auto &unit : getCurrentPlayer().getUnits()) {
        unit->resetTurn();
    }
    for (const auto &unit : getOpponentPlayer().getUnits()) {
        unit->resetTurn();
    }
    
    if (isTurnSkipped) {
        // If the turn is skipped, switch to the next player
        if (currentPlayer == 1) {
            currentPlayer = 2;
        } else {
            currentPlayer = 1;
        }
        isTurnSkipped = false;  // Reset the skip flag
    } else {
        // Switch to the next player normally
        if (currentPlayer == 1) {
            currentPlayer = 2;
        } else {
            currentPlayer = 1;
        }
    }

}

std::string TurnManager::performAction(std::string input) {
    std::string message = "";
    if(input== "move"){
        int unitId;
        std::cout<<"Enter unit id: ";
        std::cin>>unitId;
        int x,y;
        std::cout<<"Enter x and y: ";
        std::cin>>x>>y;
        Unit* unit = getCurrentPlayer().getUnit(unitId);
        if (unit) {
            if (globalGrid.moveUnit(unit->getX(), unit->getY(), x, y)) {
                unit->move(x - unit->getX(), y - unit->getY());
            } else {
                message+= "Invalid move!\n";
            }
        } else {
            message+= "Unit not found!\n";
        }

    }
    else if(input== "attack"){
        int attackerId, defenderId;
        int x,y;
        std::cout<<"Enter attacker id: ";
        std::cin>>attackerId;
        std::cout<<"Enter target location: ";
        std::cin>>x>>y;
        defenderId = globalGrid.getUnitId(x, y);
        Unit* attacker = getCurrentPlayer().getUnit(attackerId);
        Unit* defender = getOpponentPlayer().getUnit(defenderId);
        if (attacker && defender) {

            message += attacker->attack(*defender);
            getCurrentPlayer().cleanupUnits(); 
            getOpponentPlayer().cleanupUnits();
        } else {
            message +=  "Unit not found! \n";
        }

    }
    else {
        // Handle other cases if needed
    }
    return message;
}

void TurnManager::displayStatus() {
    globalGrid.displayAsciiArt(getCurrentPlayer().getPositions());
    std::cout << "Current player: " << currentPlayer << std::endl;
    getCurrentPlayer().displayInfo();   
    getCurrentPlayer().displayUnitStatus();
}
