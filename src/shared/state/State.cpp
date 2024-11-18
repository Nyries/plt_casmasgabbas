//
// Created by louismmassin on 11/8/24.
//
#include "State.h"
#include "UtilityFunctions.cpp"
#include "CircularPlayerList.cpp"

#include <iostream>

#include "RoomCard.h"
#include "SuspectCard.h"
#include "UtilityFunctions.h"
#include "WeaponCard.h"

namespace state {
    State::State(int playerCount, std::string dataFilePath): players(*this, playerCount), accusationSuccess(false),
                                                             map(std::move(dataFilePath), roomList) {
      
        roomList.emplace_back(STUDY);
        roomList.emplace_back(HALL);
        roomList.emplace_back(LIVING_ROOM);
        roomList.emplace_back(DINING_ROOM);
        roomList.emplace_back(KITCHEN);
        roomList.emplace_back(BATHROOM);
        roomList.emplace_back(GARAGE);
        roomList.emplace_back(GAME_ROOM);
        roomList.emplace_back(BEDROOM);

        roomList.at(2).addSecretPassage(roomList.at(8));
        roomList.at(8).addSecretPassage(roomList.at(2));
        roomList.at(4).addSecretPassage(roomList.at(6));
        roomList.at(6).addSecretPassage(roomList.at(4));
    }

}

