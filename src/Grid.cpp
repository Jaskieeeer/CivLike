#include "../include/Grid.h"

// Constructor (optional in this case as we initialize in the header)
Grid::Grid() {}

// Method to check if a cell is occupied
bool Grid::isCellOccupied(int x, int y) const {
    return cells[x][y] != 0;
}

// Method to set the value of a cell
void Grid::setCell(int x, int y, int value) {
    cells[x][y] = value;
}

int Grid::getWidth() const {
    return GRID_WIDTH;
}

int Grid::getHeight() const {
    return GRID_HEIGHT;
}