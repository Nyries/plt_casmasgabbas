//
// Created by louismmassin on 12/18/24.
//
#include "AIPlayer.h"

#include <utility>
namespace client {
    AIPlayer::AIPlayer(engine::Engine *engine, state::PlayerInfo &playerInfo, std::string name, ai::AI& ai): Player(engine, playerInfo, false, std::move(name)) , ai(ai){

    }

}