#include "../include/Grid.h"
#include <iostream>
#include "../include/Globals.h"
#include "../include/Cell.h"
#include <cstdlib>
#include <cmath>
Grid::Grid():  cells(GRID_WIDTH, std::vector<Cell>(GRID_HEIGHT)) {}


bool Grid::isCellOccupiedByType(int x, int y, Cell::Type type) const {
    return cells[x][y].type == type;
}

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

int Grid::getOwner(int x, int y) const {
    return cells[x][y].playerId;
}


bool Grid::canSpawnTown(int x, int y) {
    return !Grid::isCellOccupiedByType(x, y, Cell::Type::TOWN);
}

bool Grid::canAttackNeighbour(int x, int y, int playerId) {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) {
                continue; 
            }

            int neighbourX = x + dx;
            int neighbourY = y + dy;

            if (neighbourX < 0 || neighbourX >= GRID_WIDTH || neighbourY < 0 || neighbourY >= GRID_HEIGHT) {
                continue; 
            }

            if (cells[neighbourX][neighbourY].playerId != playerId) {
                return true; 
            }
        }
    }

    return false; 
}

bool Grid::moveUnit(int fromX, int fromY, int toX, int toY) {
    if (toX < 0 || toX >= GRID_WIDTH || toY < 0 || toY >= GRID_HEIGHT) {
        return false;
    }


    for (const Cell::Type& unitType : unitTypes) {
        if (cells[toX][toY].type == unitType) {
            return false; 
        }
    }

    cells[toX][toY] = cells[fromX][fromY]; 
    cells[fromX][fromY] = Cell(); 
    return true;
}

bool Grid::isVisible(int x, int y, const std::vector<std::pair<int, int>>& playerPositions) {
    const int visionRadius = 3;

    for (const auto& pos : playerPositions) {
        int playerX = pos.first;
        int playerY = pos.second;

        int dx = std::abs(x - playerX);
        int dy = std::abs(y - playerY);
        double distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= visionRadius) {
            return true;
        }
    }

    return false;
}

void Grid::displayAsciiArt(const std::vector<std::pair<int, int>>& playerPositions)  {

    std::cout << "  "; 
    for (int x = 0; x < getWidth(); ++x) {
        std::cout << x % 10 << "  "; 
    }
    std::cout << std::endl;

    for (int y = 0; y < getHeight(); ++y) {
       
        std::cout << y % 10 << " "; 

        for (int x = 0; x < getWidth(); ++x) {
            char symbol = '?';  
            std::string color = "\033[0m"; 

            bool isV = isVisible(x, y, playerPositions);
            

            if (isV) {
                switch (cells[x][y].type) {
                    case Cell::Type::EMPTY: symbol = '.'; break;
                    case Cell::Type::TOWN: symbol = 'T'; break;
                    case Cell::Type::WARRIOR: symbol = 'W'; break;
                    case Cell::Type::SETTLER: symbol = 'S'; break;
                    default: symbol = '?'; break;
                }

                switch (cells[x][y].playerId) {
                    case 1: color = "\033[1;34m"; break; 
                    case 2: color = "\033[1;31m"; break;  
                    default: color = "\033[0m"; break;    
                }
            }

            std::cout << color << symbol << "  ";
        }

        std::cout << "\033[0m" << std::endl;
    }

    std::cout << std::endl;
}
