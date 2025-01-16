//
// Created by louismmassin on 12/18/24.
//
#include "AI.h"
namespace ai {
    AI::AI(engine::Engine &engine, state::PlayerState &playerState): engine(engine), playerState(playerState), map(engine.getState().getMap()) {
    }

}