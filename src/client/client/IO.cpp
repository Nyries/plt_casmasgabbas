//
// Created by louismmassin on 1/8/25.
//
#include "IO.h"

#include "Player.h"
#include "PlayerList.h"

namespace client {
    IO::IO() = default;

    void IO::displayDiceResult(PlayerList &playerList, int result, const Player &player) {
        for (auto& currentPlayer: playerList.getVector()) {
            currentPlayer->displayDiceResult(result, player);
        }
    }

    void IO::startOfTheGame(PlayerList &playerList) {
        for (auto& currentPlayer: playerList.getVector()) {
            currentPlayer->startOfTheGame();
        }
    }

    void IO::seeHypothesisResponse(PlayerList& playerList, const state::TripleClue &hypothesis, const Player &askedPlayer, bool response) {
        for (auto& currentPlayer: playerList.getVector()) {
            currentPlayer->seeHypothesisResponse(hypothesis, askedPlayer, response);
        }
    }


}
