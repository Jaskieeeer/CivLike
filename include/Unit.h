#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include "Town.h"
class Player; 
class Town;
class Unit {
protected:
    static int idCounter; 
    int x, y; 
    int health;
    int attackPower; 
    int defense;
    int movementSpeed;
    int id;
    int usedMovementSpeed = 0; 
    bool didAttack = false;
    Player* owner;  
    bool markedForDeletion = false;  

public:
    Unit(int x, int y, Player* player);
    virtual Player* getOwner() const;
    virtual void setOwner(Player* player);
    virtual void setMovementSpeed(int speed); 
    virtual bool move(int dx, int dy); 
    virtual std::string attack(Unit& target); 
    virtual std::string attack(Town& target); 
    virtual void defend(int damage); 
    virtual void displayStatus() const; 
    virtual int getX() const; 
    virtual int getY() const;  
    virtual int getId() const;
    virtual int getHealth() const; 
    virtual int getAttack() const;
    virtual int getDefense() const; 
    virtual int getCost() const; 
    virtual int getMovementSpeed() const;
    virtual int getUsedMovementSpeed() const; 
    virtual void resetTurn();
    virtual std::vector<std::string> getActions() const; 
    void displayActions() const; 
    virtual bool isSettler() const {return false;}
    virtual bool isWarrior() const {return false;} 
    bool isMarkedForDeletion() const { return markedForDeletion; }
    virtual ~Unit(); 

};

#endif
