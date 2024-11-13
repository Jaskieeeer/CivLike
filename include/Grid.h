#ifndef GRID_H
#define GRID_H

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 10;

class Grid {
public:
    int cells[GRID_WIDTH][GRID_HEIGHT] = {0}; // Initialize all cells to 0

    Grid();
    bool isCellOccupied(int x, int y) const;
    void setCell(int x, int y, int value);
};

#endif // GRID_H
