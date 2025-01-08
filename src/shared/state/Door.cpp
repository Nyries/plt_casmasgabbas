//
// Created by Nyries on 11/18/24.
//

#include "Door.h"

namespace state {
    Door::Door(int coordX, int coordY, Room *room): Cell(coordX, coordY, LocationType::DOOR), room(room)
    {
        room->addDoor(*this);
    }
    state::Room *Door::getRoom()
    {
        return room;
    }
}