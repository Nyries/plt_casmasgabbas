//
// Created by louismmassin on 11/8/24.
//
#include "State.h"

namespace state {
    State::State(int playerCount, std::string dataFilePath): players(*this, playerCount), accusationSuccess(false) {
    }
}