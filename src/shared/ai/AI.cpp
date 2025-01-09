//
// Created by louismmassin on 12/18/24.
//
#include "AI.h"
namespace ai {
    AI::AI(engine::Engine &engine, state::PlayerInfo &playerInfo): engine(engine), playerInfo(playerInfo), map(engine.getState().getMap()) {
    }

}