//
// Created by louismmassin on 1/4/25.
//
#include "RandomAI.h"

#include <engine/Engine.h>
#include <engine/UtilityFunctions.h>

namespace ai {
    RandomAI::RandomAI(engine::Engine &engine, state::PlayerInfo &playerInfo):AI(engine, playerInfo) {
    }

    engine::CommandId RandomAI::chooseAction() {
        auto possibleActions = engine.getPossibleActions(playerInfo);
        const int randomIndex = engine::UtilityFunctions::randomInt(possibleActions.size());
        return possibleActions.at(randomIndex);
    }

    engine::Move RandomAI::chooseMoveDirection() {
        auto possibleMoves = engine.getPossibleMoves(playerInfo);
        const int randomIndex = engine::UtilityFunctions::randomInt(possibleMoves.size());
        return possibleMoves.at(randomIndex);
    }

    int RandomAI::chooseACardToShowClient(const std::vector<state::Card*>& cards) {
        const int randomIndex = engine::UtilityFunctions::randomInt(cards.size());
        return randomIndex;
    }



}
