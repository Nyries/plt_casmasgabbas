//
// Created by louismmassin on 11/8/24.
//
#include "State.h"
#include "UtilityFunctions.cpp"
#include "CircularPlayerList.cpp"

namespace state {
    State::State(int playerCount, std::string dataFilePath): players(*this, playerCount), accusationSuccess(false),
                                                             map(std::move(dataFilePath)) {
        //TODO: Initialization of the Rooms

    }

}
