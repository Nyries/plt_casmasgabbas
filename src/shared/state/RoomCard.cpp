//
// Created by louismmassin on 11/4/24.
//
#include "RoomCard.h"

namespace state {
    RoomCard::RoomCard(RoomName value): Card(ROOM_CARD), room(value) {
    }

    RoomName RoomCard::getValue() {
        return room;
    }

}
