#include "../include/Unit.h"
#include <iostream>
#include "../include/Globals.h"
#include "../include/Player.h"
#include "../include/Grid.h"
#include <cmath>
int Unit::idCounter = 0;  
Unit::Unit(int x, int y, Player *player)
    :x(x),y(y),owner(player){
        
        id=++idCounter;
        health=0;
        attackPower=0;
        defense=0;
        movementSpeed=0;
    }

Unit::~Unit() {
    if (markedForDeletion && owner) {
        owner->removeUnit(id);
    }
}

void Unit::setMovementSpeed(int speed) {
    movementSpeed = speed;
}


bool Unit::move(int dx, int dy) {
    if (globalGrid.getCellType(x + dx, y + dy) != Cell::Type::EMPTY) {
        return false;
    }
    int distanceTravelled = std::sqrt(std::pow(dx,2) + std::pow(dy,2));
    if (distanceTravelled > movementSpeed - usedMovementSpeed) {
        return false;
    }
    if (x + dx < 0 || x + dx >= globalGrid.getWidth() || y + dy < 0 || y + dy >= globalGrid.getHeight()) {
        return false;
    }

    usedMovementSpeed += distanceTravelled;
    globalGrid.moveUnit(x, y, x + dx, y + dy);
    x += dx;
    y += dy;
    return true;
}
int Unit::getCost() const {
    return 0;  
}
std::string Unit::attack(Unit& target) {
    if (didAttack) {
        return "Unit has already attacked this turn! \n";
    }
    if (std::abs(x - target.getX()) > 1 || std::abs(y - target.getY()) > 1) {
        return "Target is out of range! \n";
    }
    didAttack = true;
    int damage = attackPower *(1- target.getDefense()*0.01);
    int retaliation = target.getAttack()*(1-defense*0.01)/2;
    if (damage > 0) {
        target.defend(damage);
        this->defend(retaliation);
        if (target.isMarkedForDeletion()){
            this->move(target.getX()-x,target.getY()-y);
        }
        this->usedMovementSpeed = movementSpeed;
        return "Attacked unit! Target health: " + std::to_string(target.health) + " Your health:"+ std::to_string(health)+"\n";
    }
    return "No damage dealt! \n";
}

std::string Unit::attack(Town& target) {
    if (didAttack) {
        return "Unit has already attacked this turn! \n";
    }
    if (std::abs(x - target.getX()) > 1 || std::abs(y - target.getY()) > 1) {
        return "Target is out of range! \n";
    }
    didAttack = true;
    int damage = attackPower *(0.5);
    if (damage > 0) {
        target.defend(damage,owner);
        this->usedMovementSpeed = movementSpeed;
        return "Attacked town! Town health: " + std::to_string(target.getHealth()) + "\n";
    }
    return "No damage dealt! \n";
}

void Unit::defend(int damage) {
    health -= damage;
    if (health <= 0) {

        owner->removeUnit(id);
        markedForDeletion = true;
        globalGrid.setCell(x, y, Cell::Type::EMPTY, 0, 0);
    }
}

std::vector<std::string> Unit::getActions() const {
    std::vector<std::string> actions;
    actions.push_back("Skip(s)");
    actions.push_back("Previous(p)");
    if (movementSpeed - usedMovementSpeed >= 1) {
        actions.push_back("Move(m)");
    }
    if (!didAttack && globalGrid.canAttackNeighbour(x, y, owner->getPlayerID())) {
        actions.push_back("Attack(a)");
    }
    return actions;
}

void Unit::displayActions() const {
    std::vector<std::string> actions = getActions();
    std::cout << "Possible actions: ";
    for (const auto& action : actions) {
        std::cout << action << " ";
    }
    std::cout << std::endl;
}

Player* Unit::getOwner() const {
    return owner;
}

void Unit::setOwner(Player* player) {
    owner = player;
}

int Unit::getUsedMovementSpeed() const {
    return usedMovementSpeed;
}

int Unit::getX() const {
    return x;
}
int Unit::getY() const {
    return y;
}
int Unit::getId() const {
    return id;  
}

int Unit::getHealth() const {
    return health;
}
int Unit::getAttack() const {
    return attackPower;
}
int Unit::getDefense() const {
    return defense;
}
int Unit::getMovementSpeed() const{
    return movementSpeed;
}

void Unit::resetTurn() {
    usedMovementSpeed = 0;
    didAttack = false;
}


void Unit::displayStatus() const{
    std::cout << "Unit ID: " << id << " at (" << x << ", " << y << ") with health: " << health << ". Movement speed left: "<< movementSpeed-usedMovementSpeed<<std::endl;
}

