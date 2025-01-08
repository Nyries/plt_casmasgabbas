//
// Created by louismmassin on 11/4/24.
//

#include "Room.h"

namespace state {
    Room::Room(RoomName name): Location(ROOM), name(name),doorList(), secretPassage(nullptr) {
    }

    RoomName Room::getRoomName() {
        return name;
    }

    std::string Room::getNameAsString()
    {
        if (name == STUDY)
            return "STUDY";
        else if (name == HALL)
            return "HALL";
        else if (name == LIVING_ROOM)
            return "LIVING_ROOM";
        else if (name == DINING_ROOM)
            return "DINING_ROOM";
        else if (name == KITCHEN)
            return "KITCHEN";
        else if (name == BATHROOM)
            return "BATHROOM";
        else if (name == GARAGE)
            return "GARAGE";
        else if (name == GAME_ROOM)
            return "GAME_ROOM";
        else if (name == BEDROOM)
            return "BEDROOM";
        else
            return "ERROR";
    }

    std::vector<Door *> &Room::getDoorList() {
        return doorList;
    }

    Room* Room::getSecretPassage () {
        return secretPassage;
    }

    void Room::setSecretPassage(Room &targetRoom) {
        secretPassage = &targetRoom;
    }

    void Room::addDoor(Door &door) {
        doorList.push_back(&door);
    }


}