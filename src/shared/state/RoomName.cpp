//
// Created by louismmassin on 1/9/25.
//
#include "RoomName.h"

#include <ostream>

namespace state {
    std::ostream& operator<<(std::ostream& os, RoomName roomName) {
        switch (roomName) {
            case STUDY:
                os << "study";
            break;
            case HALL:
                os << "hall";
            break;
            case LIVING_ROOM:
                os << "living room";
            break;
            case DINING_ROOM:
                os << "dining room";
            break;
            case KITCHEN:
                os << "kitchen";
            break;
            case BATHROOM:
                os << "bathroom";
            break;
            case GARAGE:
                os << "garage";
            break;
            case GAME_ROOM:
                os << "game room";
            break;
            case BEDROOM:
                os << "bedroom";
            break;
            default:
                throw std::invalid_argument("invalid room name value");
        }
        return os;
    }
}
