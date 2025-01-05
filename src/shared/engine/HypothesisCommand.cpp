//
// Created by louismmassin on 12/16/24.
//
#include "HypothesisCommand.h"

#include <algorithm>

#include "Engine.h"

namespace engine {
    HypothesisCommand::HypothesisCommand(Engine &engine, state::PlayerInfo &player, const state::TripleClue &hypothesis): Command(engine, player, HYPOTHESIS), hypothesis(hypothesis) {

    }


    void HypothesisCommand::execute() {
        std::vector<state::PlayerInfo>& playerInfoVec = engine.getState().getPlayerInfoVec();
        auto it = std::find_if(playerInfoVec.begin(), playerInfoVec.end(),
            [suspect = hypothesis.suspect](state::PlayerInfo& element) {
                return element.getIdentity() == suspect;
            });
        if (it != playerInfoVec.end()) {
            it->setLocation(player.getLocation());
        }
    }

}
