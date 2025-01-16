//
// Created by louismmassin on 11/4/24.
//

#include "Card.h"

#include <sstream>

#include "RoomCard.h"
#include "SuspectCard.h"
#include "WeaponCard.h"
#include "Weapon.hpp"
#include "Suspect.hpp"
#include "RoomName.hpp"


namespace state {
    class RoomCard;
    class WeaponCard;
    class SuspectCard;

    Card::Card(CardType type): type(type) {
    }

    CardType Card::getType() const {
        return type;
    }

    std::string Card::getValueAsString() const {
        std::ostringstream oss;
        if (getType() == state::SUSPECT_CARD) {
            const auto& castCard = static_cast<const state::SuspectCard&>(*this);
            oss << castCard.getSuspectName();
        }
        else if (getType() == state::WEAPON_CARD) {
            const auto& castCard = static_cast<const state::WeaponCard&>(*this);
            oss << castCard.getWeaponName();
        }
        else {
            const auto& castCard = static_cast<const state::RoomCard&>(*this);
            oss << castCard.getRoomName();
        }
        return oss.str();
    }

}
