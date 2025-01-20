//
// Created by louismmassin on 1/20/25.
//
#include "EmptyIO.h"
namespace client {
    EmptyIO::EmptyIO() = default;

    int EmptyIO::introductionToTheGame() {
        return 4;
    }

    void EmptyIO::diceThrow() {

    }

    void EmptyIO::updatePlayerPositions() {

    }

    void EmptyIO::displayHypothesis(const Player &player, const state::TripleClue &hypothesis) {

    }

    void EmptyIO::displayAccusation(const Player &player, const state::TripleClue &accusation) {

    }


    void EmptyIO::displayGameEnd(const Player &winner) {

    }

    void EmptyIO::updateIO() {

    }


}