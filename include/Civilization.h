#ifndef CIVILIZATION_H
#define CIVILIZATION_H

#include <string>

class Civilization {

   

public:
    Civilization();

    virtual std::string getName() const;
    virtual int getStartingGold() const;
private:
    std::string name;  
    int starting_gold;  
};

#endif // CIVILIZATION_H
