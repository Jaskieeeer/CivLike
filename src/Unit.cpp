#include "../include/Unit.h"
#include <iostream>
#include "../include/Globals.h"
#include "../include/Player.h"
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



void Unit::setMovementSpeed(int speed) {
    movementSpeed = speed;
}

void Unit::move(int dx, int dy) {
    int distanceTravelled = std::sqrt(std::pow(dx,2) + std::pow(dy,2));
    if (distanceTravelled > movementSpeed - usedMovementSpeed) {
        std::cout << "Cannot move that far!" << std::endl;
        return;
    }
    if (x + dx < 0 || x + dx >= globalGrid.getWidth() || y + dy < 0 || y + dy >= globalGrid.getHeight()) {
        std::cout << "Cannot move outside the grid!" << std::endl;
        return;
    }
    usedMovementSpeed += distanceTravelled;
    x += dx;
    y += dy;
}

void Unit::attack(Unit& target) {
    if (didAttack) {
        std::cout << "Unit has already attacked this turn!" << std::endl;
        return;
    }
    if (std::abs(x - target.getX()) > 1 || std::abs(y - target.getY()) > 1) {
        std::cout << "Target is out of range!" << std::endl;
        return;
    }
    didAttack = true;
    int damage = attackPower - target.getDefense();
    if (damage > 0) {
        target.defend(damage);
        std::cout << "Attacked unit! Target health: " << target.health << std::endl;
    }
}

void Unit::defend(int damage) {
    health -= damage;
    if (health <= 0) {
        owner->removeUnit(id);
    }
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

void Unit::displayStatus() {
    std::cout << "Unit ID: " << id << " at (" << x << ", " << y << ") with health: " << health << std::endl;
}

