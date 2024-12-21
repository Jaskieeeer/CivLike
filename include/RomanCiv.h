#ifndef ROMANCIV_H
#define ROMANCIV_H

#include "Civilization.h"

class RomanCiv : public Civilization {

public:
    RomanCiv(); 
    std::string getName() const override;  
    int getStartingGold() const override;
private:
    std::string name;  
    int starting_gold;
};

#endif
