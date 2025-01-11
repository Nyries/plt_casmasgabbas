//
// Created by louismmassin on 11/8/24.
//
#include "State.h"

#include <fstream>
#include <json/json.h>

namespace state {
    State::State(const std::string& mapJsonPath, int playerCount): envelope(), map(mapJsonPath), playerStateVec(playerCount, PlayerState(PERVENCHE)), currentPlayer(playerStateVec.front()), accusationSuccess(false){
    }

    Map& State::getMap() {
        return map;
    }

    TripleClue State::getEnvelope() const {
        return envelope;
    }


    std::vector<PlayerState> &State::getPlayerStateVec() {
        return playerStateVec;
    }

    bool State::getAccusationSuccess() const{
        return accusationSuccess;
    }

    void State::setAccusationSuccess(bool accusationSuccess) {
        this->accusationSuccess = accusationSuccess;
    }

    PlayerState &State::getCurrentPlayer() {
        return currentPlayer;
    }

    void State::setCurrentPlayer(PlayerState &currentPlayer) {
        this->currentPlayer = currentPlayer;
    }

    Cell &State::convertSuspectToStartingCell(Suspect suspect) {
        switch (suspect) {
            case ROSE:
                return map.getCell(9,25);
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
