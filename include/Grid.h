#ifndef GRID_H
#define GRID_H
#include "Cell.h"
#include <vector>
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class Grid {
private:
    std::vector<std::vector<Cell>> cells;
public:
    Grid();
    bool isCellOccupiedByType(int x, int y, Cell::Type type) const;
    Cell::Type getCellType(int x, int y) const;
    int getOwner(int x, int y) const;
    int getUnitId(int x, int y) const;
    void setCell(int x, int y,Cell::Type type, int id, int playerId);
    int getWidth() const;
    int getHeight() const;
    bool canSpawnTown(int x, int y);
    bool canAttackNeighbour(int x, int y, int playerId);
    void displayAsciiArt(const std::vector<std::pair<int, int>>& playerPositions);
    bool moveUnit(int fromX, int fromY, int toX, int toY);
};

#endif // GRID_H
