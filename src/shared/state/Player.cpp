//
// Created by louismmassin on 11/8/24.
//
#include "Player.h"

namespace state {
    Player::Player(State& currentGame, Location &startingLocation, std::string name, Suspect identity): currentGame(currentGame),
        location(startingLocation), name(std::move(name)), identity(identity), canWin(true) {
    }
}