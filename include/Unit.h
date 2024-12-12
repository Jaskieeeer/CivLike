#ifndef UNIT_H
#define UNIT_H

#include <string>
class Player;  // Forward declaration


class Unit {
protected:
    static int idCounter;  // Static counter for generating unique IDs
    int x, y;  // Coordinates on the grid
    int health;
    int attackPower; 
    int defense;
    int movementSpeed;
    int id;
    int usedMovementSpeed = 0; 
    bool didAttack = false;
    Player* owner;  // Pointer to the player who owns the town
    bool markedForDeletion = false;  // Flag to mark the unit for deletion


public:
    Unit(int x, int y, Player* player);
    virtual Player* getOwner() const;
    virtual void setOwner(Player* player);
    virtual void setMovementSpeed(int speed); // Setter for movement speed
    virtual std::string move(int dx, int dy); // Virtual to allow overriding
    virtual std::string attack(Unit& target); // Make this method virtual for polymorphism
    virtual void defend(int damage); // Reduce health by damage
    virtual void displayStatus() const;  // For debugging
    virtual int getX() const;  // Getter for x coordinate
    virtual int getY() const;  // Getter for y coordinate
    virtual int getId() const; // Getter for unit ID
    virtual int getHealth() const; // Getter for health
    virtual int getAttack() const; // Getter for attack power
    virtual int getDefense() const; // Getter for defense
    virtual int getMovementSpeed() const; // Getter for movement speed
    virtual int getUsedMovementSpeed() const; // Getter for used movement speed 
    virtual void resetTurn(); // Reset movement and attack status at the end of a turn
    bool isMarkedForDeletion() const { return markedForDeletion; }
    virtual ~Unit() {} // Virtual destructor to ensure proper cleanup of derived class objects

};

#endif // UNIT_H
