#ifndef GRID_H
#define GRID_H

const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;

class Grid {
public:
    int cells[GRID_WIDTH][GRID_HEIGHT] = {0}; // Initialize all cells to 0

    Grid();
    bool isCellOccupied(int x, int y) const;
    void setCell(int x, int y, int value);
    int getWidth() const;
    int getHeight() const;
};

#endif // GRID_H
