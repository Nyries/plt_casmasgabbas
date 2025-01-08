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
        state::Suspect teleportedSuspect = hypothesis.suspect;
        const auto teleportedPlayer = std::find_if(playerInfoVec.begin(), playerInfoVec.end(),
            [teleportedSuspect](state::PlayerInfo& i){
                return teleportedSuspect == i.getIdentity();
            });
        if (teleportedPlayer != playerInfoVec.end()) {
            teleportedPlayer->setLocation(player.getLocation());
        }
    }
}
