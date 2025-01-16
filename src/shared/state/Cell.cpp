//
// Created by louismmassin on 11/4/24.
//
#include "Cell.h"
#include "Map.h"
namespace state {
    Cell::Cell(int X, int Y, LocationType type): Location(type), X(X), Y(Y), player(nullptr) {
    }

    Cell::~Cell()
    = default;

    int Cell::getX() const{
        return X;
    }

    int Cell::getY() const {
        return Y;
    }

    void Cell::setCell(int X, int Y, LocationType type)
    {
        this->X = X;
        this->Y = Y;
        this->type = type;
    }

    bool Cell::getOccupied() const {
        return player!=nullptr;
    }

    const PlayerState *Cell::getPlayer() const {
        return player;
    }

    void Cell::setPlayer(const PlayerState *player) {
        this->player = player;
    }


}
