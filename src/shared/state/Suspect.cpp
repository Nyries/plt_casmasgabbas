//
// Created by louismmassin on 1/9/25.
//
#include "Suspect.h"
#include "TripleClue.h"

#include <ostream>

namespace state {
    std::ostream& operator<<(std::ostream& os, Suspect suspect) {
        switch (suspect) {
            case ROSE:
                os << "Rose";
            break;
            case PERVENCHE:
                os << "Pervenche";
            break;
            case LEBLANC:
                os << "Leblanc";
            break;
            case OLIVE:
                os << "Olive";
            break;
            case MOUTARDE:
                os << "Moutarde";
            break;
            case VIOLET:
                os << "Violet";
            break;
        }
        return os;
    }
}
