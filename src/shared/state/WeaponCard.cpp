//
// Created by louismmassin on 11/4/24.
//
#include "WeaponCard.h"

namespace state {
    WeaponCard::WeaponCard(Weapon value): Card(WEAPON_CARD), weapon(value) {
    }

    Weapon WeaponCard::getWeaponName() const{
        return weapon;
    }

}
