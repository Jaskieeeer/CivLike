#include "../include/Building.h"
#include <iostream>

Building::Building(Type type, int cost) : type(type), cost(cost), isBuilt(false) {}

void Building::build() {
    isBuilt = true;
    std::cout << "Building constructed." << std::endl;
}

void Building::effect() {
    // Implement effects based on building type
    if (type == Type::Farm) {
        std::cout << "Producing food from the farm!" << std::endl;
    } else if (type == Type::Barracks) {
        std::cout << "Training units in the barracks." << std::endl;
    } else if (type == Type::Market) {
        std::cout << "Trading resources at the market." << std::endl;
    }
}
