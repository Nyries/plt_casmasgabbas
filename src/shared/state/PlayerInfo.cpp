//
// Created by louismmassin on 11/8/24.
//
#include "PlayerInfo.h"

#include <utility>

namespace state {
    PlayerInfo::PlayerInfo(Suspect identity):cards(), location(nullptr),  identity(identity), canWin(true), previousHypothesisRoom(state::NO_ROOM) {
    }

    void PlayerInfo::setLocation(Location &newLocation) {
        this->location = &newLocation;
    }

    std::vector<Card>& PlayerInfo::getCards () {
        return cards;
    }

    void PlayerInfo::giveCard(Card &card) {
        cards.push_back(std::move(card));
    }

    Location& PlayerInfo::getLocation () {
        return *location;
    }

    const Location &PlayerInfo::getLocation() const {
        return *location;
    }


    Suspect PlayerInfo::getIdentity () const {
        return identity;
    }

    void PlayerInfo::setIdentity(Suspect identity) {
        this->identity = identity;
    }

    bool PlayerInfo::getCanWin() {
        return canWin;
    }

    void PlayerInfo::setCanWin(bool accusationFailed) {
        this->canWin = accusationFailed;
    }

    RoomName PlayerInfo::getPreviousHypothesisRoom () const{
        return previousHypothesisRoom;
    }
    void PlayerInfo::setPreviousHypothesisRoom (RoomName room) {
        this->previousHypothesisRoom = room;
    }

    void PlayerInfo::addSuspectCard(SuspectCard &card) {
        suspectCards.push_back(std::move(card));
    }

    void PlayerInfo::addWeaponCard(WeaponCard &card) {
        weaponCards.push_back(std::move(card));
    }

    void PlayerInfo::addRoomCard(RoomCard &card) {
        roomCards.push_back(std::move(card));
    }

    const std::vector<SuspectCard> &PlayerInfo::getSuspectCards() {
        return suspectCards;
    }

    const std::vector<WeaponCard> &PlayerInfo::getWeaponCards() {
        return weaponCards;
    }

    const std::vector<RoomCard> &PlayerInfo::getRoomCards() {
        return roomCards;
    }


}