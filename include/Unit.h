#ifndef UNIT_H
#define UNIT_H

class Unit {
protected:
    static int idCounter;  // Static counter for generating unique IDs
    int x, y;  // Coordinates on the grid
    int health;
    int attackPower; 
    int defense;
    int movementSpeed;
    int id;

public:
    Unit(int x, int y);
    
    virtual void move(int dx, int dy); // Virtual to allow overriding
    virtual void attack(Unit& target); // Make this method virtual for polymorphism
    virtual void displayStatus();  // For debugging
    virtual int getX() const;  // Getter for x coordinate
    virtual int getY() const;  // Getter for y coordinate
    virtual int getId() const; // Getter for unit ID
    virtual int getHealth() const; // Getter for health
    virtual int getAttack() const; // Getter for attack power
    virtual int getDefense() const; // Getter for defense
    virtual int getMovementSpeed() const; // Getter for movement speed
    virtual ~Unit() {} // Virtual destructor to ensure proper cleanup of derived class objects
};

#endif // UNIT_H
