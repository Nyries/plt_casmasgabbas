//
// Created by louismmassin on 11/4/24.
//
#include "Cell.h"
namespace state {
    Cell::Cell(int coordX, int coordY, LocationType type): Location(type), coordX(coordX), coordY(coordY), occupied(false) {
    }

    Cell::~Cell()
    = default;

    int Cell::getX() {
        return coordX;
    }

    int Cell::getY() {
        return coordY;
    }

    void Cell::setCell(int coordX, int coordY, LocationType type)
    {
        this->coordX = coordX;
        this->coordY = coordY;
        this->type = type;
    }

    bool Cell::getOccupied() const {
        return occupied;
    }

    void Cell::setOccupied(bool occupied) {
        this->occupied = occupied;
    }


}
