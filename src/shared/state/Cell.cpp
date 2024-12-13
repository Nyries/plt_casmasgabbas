//
// Created by louismmassin on 11/4/24.
//
#include "Cell.h"
#include "Map.h"
namespace state {
    Cell::Cell(int X, int Y, LocationType type): Location(type), X(X), Y(Y), occupied(false) {
    }

    Cell::~Cell()
    = default;

    int Cell::getX() {
        return X;
    }

    int Cell::getY() {
        return Y;
    }

    void Cell::setCell(int X, int Y, LocationType type)
    {
        this->X = X;
        this->Y = Y;
        this->type = type;
    }

    bool Cell::getOccupied() const {
        return occupied;
    }

    void Cell::setOccupied(bool occupied) {
        this->occupied = occupied;
    }

    /*std::vector<Cell *> Cell::getAccessibleCells() {
        std::vector<Cell*> accessibleCells;

        std::vector<std::pair<int, int>> directions = {
                {0, -1}, // Up
                {0, 1},  // Down
                {-1, 0}, // Left
                {1, 0}   // Right
        };

        for (const auto& [dx, dy] : directions) {
            int newX = coordX + dx;
            int newY = coordY + dy;

            // Vérifier les limites via Map::getCell
            Cell neighbor = Map::getCell(newX, newY);
            if (neighbor != nullptr && (neighbor.getType() == CORRIDOR || neighbor.getType() == DOOR)) {
                neighbors.push_back(neighbor);
            }
        }

        return accessibleCells;
    }*/


}
