#include "../include/Grid.h"

// Constructor (optional in this case as we initialize in the header)
Grid::Grid():  cells(GRID_WIDTH, std::vector<Cell>(GRID_HEIGHT)) {}

// Method to check if a cell is occupied

bool Grid::isCellOccupied(int x, int y, Cell::Type type) const {
    return cells[x][y].type == type;
}

// Method to set the value of a cell
void Grid::setCell(int x, int y, Cell::Type type, int id) {
    cells[x][y].type = type;
    cells[x][y].id = id;
}

int Grid::getWidth() const {
    return GRID_WIDTH;
}

int Grid::getHeight() const {
    return GRID_HEIGHT;
}

bool Grid::canSpawnTown(int x, int y) {
    return !Grid::isCellOccupied(x, y, Cell::Type::TOWN);
}