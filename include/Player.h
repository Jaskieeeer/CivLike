#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Unit.h"
#include "Town.h"
#include "Building.h"
#include "Civilization.h"
#include "Gold.h"

class Player {
private:
    static int playerIdCounter;  
    int playerID;         
    std::string name;    
    Civilization* civilization; 
    std::vector<Unit*> units;    
    std::vector<Town*> towns;   
    Gold<int> gold;              
    int goldIncome;        
public:
    

    Player(std::string name, Civilization* civ);
    ~Player();


    void addUnit(Unit* unit);  
    void removeUnit(int unitId);  


    void transformUnitIntoTown(int unitID);

    void cleanupUnits();
    void addTown(Town* town);  
    void loseTown(Town* town,Player* player = nullptr);  

    bool hasSettlersOrTowns();


    // Getters

    int getPlayerID() const;
    const std::string& getName() const;
    Civilization* getCivilization() const;
    const std::vector<Unit*>& getUnits() const;
    Unit* getUnit(int unitID) const;
    const std::vector<Town*>& getTowns() const;
    Town* getTown(int townID) const;
    int getGold() const;
    void setGold(int gold);
    std::vector<std::pair<int, int>> getPositions() const;
    void updateIncome();
    void updateGold();
    void printPositions() const;
    void displayUnitStatus() const;
    void displayTownStatus() const;
    void displayInfo() const;


};

#endif 
