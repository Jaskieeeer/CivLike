#include "../include/Grid.h"
#include <iostream>
#include "../include/Globals.h"
#include "../include/Cell.h"
#include <cstdlib>
// Constructor (optional in this case as we initialize in the header)
Grid::Grid():  cells(GRID_WIDTH, std::vector<Cell>(GRID_HEIGHT)) {}

// Method to check if a cell is occupied

bool Grid::isCellOccupiedByType(int x, int y, Cell::Type type) const {
    return cells[x][y].type == type;
}

// Method to set the value of a cell
void Grid::setCell(int x, int y, Cell::Type type, int id,int playerId) {
    cells[x][y].type = type;
    cells[x][y].id = id;
    cells[x][y].playerId = playerId;
}

int Grid::getWidth() const {
    return GRID_WIDTH;
}

int Grid::getHeight() const {
    return GRID_HEIGHT;

}

Cell::Type Grid::getCellType(int x, int y) const {
    return cells[x][y].type;
}

int Grid::getUnitId(int x, int y) const {
    return cells[x][y].id;
}

bool Grid::canSpawnTown(int x, int y) {
    return !Grid::isCellOccupiedByType(x, y, Cell::Type::TOWN);
}

bool Grid::moveUnit(int fromX, int fromY, int toX, int toY) {
    // Check bounds
    if (toX < 0 || toX >= GRID_WIDTH || toY < 0 || toY >= GRID_HEIGHT) {
        return false; // Out of bounds
    }

    // Check if destination is occupied or not walkable

    for (const Cell::Type& unitType : unitTypes) {
        if (cells[toX][toY].type == unitType) {
            return false; // Cell is occupied by a unit type
        }
    }

    // Perform movement
    cells[toX][toY] = cells[fromX][fromY]; // Copy unit data
    cells[fromX][fromY] = Cell(); // Clear previous cell
    return true;
}


void Grid::displayAsciiArt() const {
    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            char symbol = ' '; // Default symbol for empty cells
            switch (cells[x][y].type) {
                case Cell::Type::EMPTY: symbol = '.'; break;  // Empty cell
                case Cell::Type::TOWN: symbol = 'T'; break;  // Town
                case Cell::Type::WARRIOR: symbol = 'W'; break;  // Warrior
                case Cell::Type::SETTLER: symbol = 'S'; break;  // Settler
                default: symbol = '?'; break;               // Unknown type
            }
            std::string color = "";
            switch (cells[x][y].playerId) {
                case 1: color = "\033[1;34m"; break;  // Red
                case 2: color = "\033[1;31m"; break;  // Blue
                default: color = "\033[0m"; break;    // Reset
            }
            std::cout << color << symbol << "  ";
        }
        std::cout<< std::endl;
    }
    std::cout<< std::endl;
}