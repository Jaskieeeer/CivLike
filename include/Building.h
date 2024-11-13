#ifndef BUILDING_H
#define BUILDING_H

class Building {
public:
    enum class Type { Barracks, Farm, Market, Workshop };  // Types of buildings
    Type type;
    int cost;
    bool isBuilt;

    Building(Type type, int cost);
    void build();  // Set building status to 'built'
    void effect(); // Apply the building's effect (e.g., resource production, unit training)
};

#endif // BUILDING_H
