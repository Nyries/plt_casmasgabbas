//
// Created by louismmassin on 10/21/24.
//
#include "Map.h"
#include "LocationType.h"

namespace state {
    Map::Map(std::string jsonPath, std::vector<Room> &roomList) {
        
    }

    LocationType Map::getType(int coordX, int coordY) {
        return array.at(coordY).at(coordX).getType();
    }

}

