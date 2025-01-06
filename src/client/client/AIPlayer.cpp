//
// Created by louismmassin on 12/18/24.
//
#include "AIPlayer.h"

#include <utility>
#include <ai/RandomAI.h>

namespace client {
    AIPlayer::AIPlayer(engine::Engine &engine, state::PlayerInfo &playerInfo, std::string name, std::unique_ptr<ai::AI> ai): Player(engine, playerInfo, false, name) , ai(move(ai)){
    }

    engine::CommandId AIPlayer::chooseAction() {
        return ai->chooseAction();
    }

    engine::Move AIPlayer::chooseMoveDirection() {
        return ai->chooseMoveDirection();
    }

    state::TripleClue AIPlayer::chooseHypothesis() {
        return ai->chooseHypothesis();
    }

    int AIPlayer::chooseACardToShowClient(const std::vector<state::Card *> &cards) {
        return ai->chooseACardToShowClient(cards);
    }

    state::TripleClue AIPlayer::chooseAccusation() {
        return ai->chooseAccusation();
    }

    void AIPlayer::showACardToPlayer(const state::Card &shownCard, const Player &cardOwner) {

    }

}
