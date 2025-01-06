//
// Created by louismmassin on 11/8/24.
//
#include "State.h"

#include <fstream>
#include <json/json.h>

namespace state {
    State::State(const std::string& mapJsonPath, int playerCount): envelope(), map(mapJsonPath), playerInfoVec(playerCount, PlayerInfo(PERVENCHE)), currentPlayer(playerInfoVec.front()), accusationSuccess(false){
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

    PlayerInfo &State::getCurrentPlayer() {
        return currentPlayer;
    }

    void State::setCurrentPlayer(PlayerInfo &currentPlayer) {
        this->currentPlayer = currentPlayer;
    }

    Location &State::suspectToStartingCell(Suspect suspect) {
        switch (suspect) {
            case ROSE:
                return map.getCell(10,25);
            case PERVENCHE:
                return map.getCell(24,7);
            case LEBLANC:
                return map.getCell(10,1);
            case OLIVE:
                return map.getCell(15,1);
            case MOUTARDE:
                return map.getCell(1,18);
            case VIOLET:
                return map.getCell(24,20);
            default:
                throw std::invalid_argument("Incorrect Suspect enum value");
        }
    }


}
