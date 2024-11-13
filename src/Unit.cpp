#include "../include/Unit.h"
#include <iostream>
int Unit::idCounter = 0;  
Unit::Unit(int health, int attackPower, int defense, int x, int y)
    : health(health), attackPower(attackPower), defense(defense),x(x),y(y) {
        id=idCounter++;
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

void Unit::displayStatus() {
    std::cout << "Unit ID: " << id << " at (" << x << ", " << y << ") with health: " << health << std::endl;
}