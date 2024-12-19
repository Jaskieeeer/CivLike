#include "RomanCiv.h"
#include <iostream>

RomanCiv::RomanCiv() {
    name = "Roman Empire";  
    starting_gold = 300;

}

std::string RomanCiv::getName() const {
    return name;
}

int RomanCiv::getStartingGold() const {
    return starting_gold;
}