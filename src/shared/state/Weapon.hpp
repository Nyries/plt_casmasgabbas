//
// Created by louismmassin on 1/10/25.
//

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "Weapon.h"
#include <ostream>

namespace state{
    std::ostream& operator<<(std::ostream& os, Weapon weapon);
    std::string toString(Weapon weapon);
}
#endif //WEAPON_HPP
