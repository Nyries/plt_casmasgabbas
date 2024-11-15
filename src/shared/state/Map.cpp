//
// Created by louismmassin on 10/21/24.
//
#include "Map.h"
#include "LocationType.h"

namespace state {
    LocationType Map::getType(int coordX, int coordY) {
        return array.at(coordY).at(coordX).getType();
    }

    Cell& Map::getCell(int coordX, int coordY) {
        return array.at(coordY).at(coordX);
    }
}
