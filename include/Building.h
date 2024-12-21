#ifndef BUILDING_H
#define BUILDING_H

#include <string>
class Building {

public:

    enum class Type { Barracks, Farm, Market};  
    Building(Type type);
    void build();  
    int getIncome() const;
    Type getType() const;
    int getCost() const;
    static std::string buildingTypeToString(Type type) ;
private:
    Type type;
    bool isBuilt;
};

#endif
