#include "../include/Unit.h"
#include <iostream>
int Unit::idCounter = 0;  
Unit::Unit(int x, int y)
    :x(x),y(y){
        id=++idCounter;
        health=0;
        attackPower=0;
        defense=0;
        movementSpeed=0;
    }

void Unit::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Unit::attack(Unit& target) {
    // Default attack logic (can be overridden by subclasses)
    int damage = attackPower - target.defense;
    if (damage > 0) {
        target.health -= damage;
        std::cout << "Attacked unit! Target health: " << target.health << std::endl;
    }
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

void Unit::displayStatus() {
    std::cout << "Unit ID: " << id << " at (" << x << ", " << y << ") with health: " << health << std::endl;
}

