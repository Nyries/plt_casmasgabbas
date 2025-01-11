//
// Created by louismmassin on 12/16/24.
//
#include "HypothesisCommand.h"

#include <algorithm>

#include "Engine.h"

namespace engine {
    HypothesisCommand::HypothesisCommand(Engine &engine, state::PlayerState &player, const state::TripleClue &hypothesis): Command(engine, player, HYPOTHESIS), hypothesis(hypothesis) {

    }


    void HypothesisCommand::execute() {
        if (&player == &engine.getCurrentPlayer() and player.getLocation().getType() == state::ROOM){
            auto& hypothesisRoom = static_cast<state::Room&>(player.getLocation());
            if (hypothesisRoom.getRoomName() == hypothesis.room) {
                std::vector<state::PlayerState>& playerStateVec = engine.getState().getPlayerStateVec();
                state::Suspect teleportedSuspect = hypothesis.suspect;
                const auto teleportedPlayer = std::find_if(playerStateVec.begin(), playerStateVec.end(),
                    [teleportedSuspect](state::PlayerState& i){
                        return teleportedSuspect == i.getIdentity();
                    });
                if (teleportedPlayer != playerStateVec.end()) {
                    teleportedPlayer->setLocation(player.getLocation());
                }
                player.setPreviousHypothesisRoom(hypothesisRoom.getRoomName());
            }
        }
    }
}
