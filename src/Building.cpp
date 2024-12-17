#include "../include/Building.h"
#include <iostream>
#include <string>

Building::Building(Type type) : type(type), isBuilt(false) {}

void Building::build() {
    isBuilt = true;
    std::cout << "Building constructed." << std::endl;
}

int Building::getCost() const {
    switch (type) {
        case Type::Barracks:
            return 250;
        case Type::Farm:
            return 150;
        case Type::Market:
            return 300;
        default:
            return 0;
    }
    
}

Building::Type Building::getType() const {
    return type;
}

std::string Building::buildingTypeToString(Type type) {
    switch (type) {
        case Type::Barracks:
            return "Barracks";
        case Type::Farm:
            return "Farm";
        case Type::Market:
            return "Market";
        default:
            return "Unknown";
    }
}


int Building::getIncome() const {
    switch (type) {
        case Type::Barracks:
            return 0;
        case Type::Farm:
            return 50;
        case Type::Market:
            return 100;
        default:
            return 0;
    }
}
