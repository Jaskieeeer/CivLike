#ifndef ROMANCIV_H
#define ROMANCIV_H

#include "Civilization.h"

class RomanCiv : public Civilization {

public:
    RomanCiv();  // Constructor
    std::string getName() const override;  // Override the base class method
    int getStartingGold() const override;  // Override the base class method
private:
    std::string name;  // Name of the Roman civilization
    int starting_gold;  // Starting gold for the Roman civilization
};

#endif // ROMANCIV_H
