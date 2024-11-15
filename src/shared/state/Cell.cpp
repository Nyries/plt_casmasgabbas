//
// Created by louismmassin on 11/4/24.
//
#include "Cell.h"
#include "Map.h"
namespace state {
    Cell::Cell(LocationType type, int coordX, int coordY): Location(type), coordX(coordX), coordY(coordY) {
    }

    int Cell::getX() {
        return coordX;
    }

    int Cell::getY() {
        return coordY;
    }

    bool Cell::getOccupied() const {
        return occupied;
    }

    void Cell::setOccupied(bool occupied) {
        this->occupied = occupied;
    }

    std::vector<Cell *> Cell::getAccessibleCells() {
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
            Cell neighbor = array.getCell(newX, newY);
            if (neighbor != nullptr && (neighbor.getType() == CORRIDOR || neighbor.getType() == DOOR)) {
                neighbors.push_back(neighbor);
            }
        }

        return accessibleCells;
    }


}
