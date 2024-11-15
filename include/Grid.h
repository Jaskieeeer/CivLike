#ifndef GRID_H
#define GRID_H
#include "Cell.h"
#include <vector>
const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
public:
    Grid();
    bool isCellOccupied(int x, int y, Cell::Type type) const;
    void setCell(int x, int y,Cell::Type type, int id);
    int getWidth() const;
    int getHeight() const;
    bool canSpawnTown(int x, int y);
};

#endif // GRID_H
