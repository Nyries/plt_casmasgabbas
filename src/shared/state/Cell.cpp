//
// Created by louismmassin on 11/4/24.
//
#include "Cell.h"
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


}
