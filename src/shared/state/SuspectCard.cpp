//
// Created by louismmassin on 11/4/24.
//
#include "SuspectCard.h"

namespace state {
    SuspectCard::SuspectCard(Suspect value): Card(SUSPECT_CARD), suspect(value) {
    }

    Suspect SuspectCard::getValue() {
        return suspect;
    }

}
