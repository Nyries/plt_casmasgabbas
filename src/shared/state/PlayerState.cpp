//
// Created by louismmassin on 11/8/24.
//
#include "PlayerState.h"

#include <utility>

#include "Location.h"

namespace state {
    PlayerState::PlayerState(Suspect identity): location(nullptr),  identity(identity), canWin(true), previousHypothesisRoom(state::NO_ROOM) {
    }

    void PlayerState::setLocation(Location &newLocation) {
        if (this->location != nullptr) {
            this->location->setPlayer(nullptr);
        }
        this->location = &newLocation;
        newLocation.setPlayer(this);
    }

    Location& PlayerState::getLocation () {
        return *location;
    }

    const Location &PlayerState::getLocation() const {
        return *location;
    }


    Suspect PlayerState::getIdentity () const {
        return identity;
    }

    void PlayerState::setIdentity(Suspect identity) {
        this->identity = identity;
    }


    bool PlayerState::getCanWin() {
        return canWin;
    }

    void PlayerState::setCanWin(bool accusationFailed) {
        this->canWin = accusationFailed;
    }

    RoomName PlayerState::getPreviousHypothesisRoom () const{
        return previousHypothesisRoom;
    }
    void PlayerState::setPreviousHypothesisRoom (RoomName room) {
        this->previousHypothesisRoom = room;
    }

    void PlayerState::addSuspectCard(SuspectCard &card) {
        suspectCards.push_back(std::move(card));
    }

    void PlayerState::addWeaponCard(WeaponCard &card) {
        weaponCards.push_back(std::move(card));
    }

    void PlayerState::addRoomCard(RoomCard &card) {
        roomCards.push_back(std::move(card));
    }

    const std::vector<SuspectCard> &PlayerState::getSuspectCards() {
        return suspectCards;
    }

    const std::vector<WeaponCard> &PlayerState::getWeaponCards() {
        return weaponCards;
    }

    const std::vector<RoomCard> &PlayerState::getRoomCards() {
        return roomCards;
    }


}
