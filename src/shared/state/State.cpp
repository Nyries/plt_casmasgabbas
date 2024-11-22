//
// Created by louismmassin on 11/8/24.
//
#include "State.h"

#include <iostream>

#include "RoomCard.h"
#include "SuspectCard.h"
#include "UtilityFunctions.h"
#include "WeaponCard.h"

namespace state {
    State::State(int playerCount, std::string dataFilePath): players(*this, playerCount), accusationSuccess(false), map(dataFilePath) {
    }

    Map &State::getMap() {
        return map;
    }

    CircularPlayerList &State::getplayerList() {
        return players;
    }

    std::vector<Card> &State::getEnvelope() {
        return envelope;
    }

}

