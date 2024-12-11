//
// Created by louismmassin on 11/8/24.
//
#include "PlayerInfo.h"

#include <utility>

namespace state {
    PlayerInfo::PlayerInfo(std::string  name, Suspect identity): location(nullptr), name(std::move(name)), identity(identity), canWin(true) {
    }

    void PlayerInfo::setLocation(Location &newLocation) {
        this->location = &newLocation;
    }

    void PlayerInfo::giveCard(Card &card) {
        cards.push_back(std::move(card));
    }

    Location& PlayerInfo::getLocation () {
        return *location;
    }

    Suspect PlayerInfo::getIdentity () {
        return identity;
    }

    void PlayerInfo::setIdentity(Suspect identity) {
        this->identity = identity;
    }


    const std::string& PlayerInfo::getName() {
        return name;
    }

    bool PlayerInfo::getCanWin() {
        return canWin;
    }

    void PlayerInfo::setCanWin(bool accusationFailed) {
        this->canWin = accusationFailed;
    }
}