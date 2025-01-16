//
// Created by louismmassin on 12/18/24.
//
#include "Player.h"

#include <utility>

#include "Client.h"

namespace client {
    Player::Player(engine::Engine &engine, state::PlayerState &playerState, bool isHuman, std::string name): engine(engine), playerState(playerState), isHuman(isHuman), name(move(name)) {

    }

    const std::string& Player::getName() const {
        return name;
    }

    state::PlayerState &Player::getPlayerState() {
        return playerState;
    }

    const state::PlayerState &Player::getPlayerState() const {
        return playerState;
    }

}
