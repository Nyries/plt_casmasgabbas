//
// Created by louismmassin on 11/8/24.
//
#include "Player.h"

namespace state {
    Player::Player(State& currentGame, std::string name, Suspect identity): currentGame(currentGame),
        location(nullptr), name(std::move(name)), identity(identity), canWin(true) {
    }

    void Player::setLocation(Location &newLocation) {
        this->location = &newLocation;
    }

    void Player::giveCard(Card &card) {
        cards.push_back(std::move(card));
    }

}