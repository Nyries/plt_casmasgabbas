//
// Created by louismmassin on 1/15/25.
//
#include "client/HumanPlayerRender.h"

namespace client {
    HumanPlayerRender::HumanPlayerRender(engine::Engine &engine, state::PlayerState &playerState, std::string name): HumanPlayer(engine, playerState, name){

    }

    void HumanPlayerRender::startOfTheGame() {

    }


    engine::CommandId HumanPlayerRender::chooseAction() {

    }

    engine::Move HumanPlayerRender::chooseMoveDirection() {

    }

    state::Door &HumanPlayerRender::chooseDoor(const std::vector<state::Door *> &doorList) {

    }


    state::TripleClue HumanPlayerRender::chooseHypothesis() {

    }

    int HumanPlayerRender::chooseACardToShowPlayer(const std::vector<const state::Card *> &cards, const Player &player) {

    }


    void HumanPlayerRender::seeACardFromPlayer(const state::Card &shownCard, const Player &cardOwner) {

    }

    state::TripleClue HumanPlayerRender::chooseAccusation() {

    }

    void HumanPlayerRender::makePlayerThrowDice() {

    }

    void HumanPlayerRender::displayDiceResult(int result, const Player &player) {

    }

}