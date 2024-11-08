//
// Created by louismmassin on 11/8/24.
//
#include "State.h"

namespace state {
    State::State(int playerCount, std::string dataFilePath): players(*this, playerCount), accusationSuccess(false),
                                                             map(std::move(dataFilePath)) {
        //TODO: Initialization of the Rooms
        roomList.emplace_back(STUDY);
        roomList.emplace_back(HALL);
        roomList.emplace_back(LIVING_ROOM);
        roomList.emplace_back(DINING_ROOM);
        roomList.emplace_back(KITCHEN);
        roomList.emplace_back(BATHROOM);
        roomList.emplace_back(STUDY);
        roomList.emplace_back(GARAGE);
        roomList.emplace_back(GAME_ROOM);
        roomList.emplace_back(BEDROOM);


    }
}
