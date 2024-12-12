

#include "../include/Warrior.h"
#include "../include/Grid.h"
#include "../include/Globals.h"
#include <iostream>

Warrior::Warrior(int x, int y, Player* player)
    : Unit(x, y, player) {
        globalGrid.setCell(x, y, Cell::Type::WARRIOR, id,player->getPlayerID());
        health=250;
        attackPower=80;
        defense=25;
        movementSpeed=5;
    }






bool Warrior::isWarrior() const {
    return true; // This is a Settler
}