//
// Created by louismmassin on 11/4/24.
//

#include "Card.h"
namespace state {
    Card::Card(CardType type): type(type) {
    }

    CardType Card::getType() {
        return type;
    }

    Suspect Card::getSuspectName() {
        return Suspect::VIOLET;
    }

    Weapon Card::getWeaponName() {
        return Weapon::WRENCH;
    }

    RoomName Card::getRoomName() {
        return RoomName::BEDROOM;
    }



}