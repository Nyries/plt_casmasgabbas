//
// Created by louismmassin on 11/8/24.
//
#include "PlayerInfo.h"

#include <utility>

namespace state {
    PlayerInfo::PlayerInfo(std::string  name, Suspect identity): currentGame(currentGame),
        location(nullptr), name(std::move(name)), identity(identity), canWin(true) {
    }

    void PlayerInfo::setLocation(Location &newLocation) {
        this->location = &newLocation;
    }

    void PlayerInfo::giveCard(Card &card) {
        cards.push_back(std::move(card));
    }

}