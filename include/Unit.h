#ifndef UNIT_H
#define UNIT_H

class Unit {
protected:
    
    int health;
    int attackPower; 
    int defense;
    int x, y;  // Coordinates on the grid
    int movementSpeed;

public:
    Unit(int health, int attackPower, int defense, int x, int y);
    
    virtual void move(int dx, int dy); // Virtual to allow overriding
    virtual void attack(Unit& target); // Make this method virtual for polymorphism
    virtual void performEconomicAction() = 0;  // Different actions for economic units
    virtual void displayStatus();  // For debugging
    virtual int getX() const;  // Getter for x coordinate
    virtual int getY() const;  // Getter for y coordinate
    virtual ~Unit() {} // Virtual destructor to ensure proper cleanup of derived class objects
};

#endif // UNIT_H
