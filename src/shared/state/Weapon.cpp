//
// Created by louismmassin on 1/9/25.
//
#include "Weapon.h"

#include <ostream>
#include <sstream>

namespace state {
    std::ostream& operator<<(std::ostream& os, Weapon weapon) {
        switch (weapon) {
            case CANDLESTICK:
                os << "candlestick";
            break;
            case PISTOL:
                os << "pistol";
            break;
            case ROPE:
                os << "rope";
            break;
            case LEAD_PIPE:
                os << "lead pipe";
            break;
            case KNIFE:
                os << "knife";
            break;
            case WRENCH:
                os << "wrench";
            break;
        }
        return os;
    }

    std::string toString(Weapon weapon) {
        std::ostringstream oss;
        oss << weapon;
        return oss.str();
    }
}
