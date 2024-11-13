#include "Civilization.h"
#include <iostream>

Civilization::Civilization() {}
    

std::string Civilization::getName() const {
    return name;
}

int Civilization::getStartingGold() const {
    return starting_gold;
}


