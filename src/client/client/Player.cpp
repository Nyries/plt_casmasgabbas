//
// Created by louismmassin on 12/18/24.
//
#include "Player.h"

#include <utility>

#include "Client.h"

namespace client {
    Player::Player(engine::Engine &engine, state::PlayerInfo &playerInfo, bool isHuman, std::string& name): engine(engine), playerInfo(playerInfo), isHuman(isHuman), name(move(name)) {

    }

    state::PlayerInfo &Player::getPlayerInfo() {
        return playerInfo;
    }

}
