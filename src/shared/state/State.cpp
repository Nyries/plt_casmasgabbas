//
// Created by louismmassin on 11/8/24.
//
#include "State.h"

#include <fstream>
#include <json/json.h>

namespace state {
    State::State(const std::string& mapJsonPath, int playerCount): accusationSuccess(false), envelope(), map(mapJsonPath), currentPlayer(playerInfoVec.front())
    {
        envelope.reserve(3);
        playerInfoVec.reserve(playerCount);
        for (int i = 0; i < playerCount; i++) {
            playerInfoVec.emplace_back(PERVENCHE);
        }
    }

    Map& State::getMap() {
        return map;
    }

    std::vector<Card> &State::getEnvelope()
    {
        return this->envelope;
    }

    std::vector<PlayerInfo> &State::getPlayerInfoVec() {
        return playerInfoVec;
    }

    bool State::getAccusationSuccess() {
        return accusationSuccess;
    }

    void State::setAccusationSuccess(bool accusationSuccess) {
        this->accusationSuccess = accusationSuccess;
    }

}
