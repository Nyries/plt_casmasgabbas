//
// Created by louismmassin on 11/4/24.
//
#include "CircularList.h"

#include <vector>

namespace state {
    CircularList::CircularList(State& currentGame, int playerCount): it(list.begin()), currentPlayer(list.front()) {
        list.reserve(playerCount);
        Location defaultLocation(INACCESSIBLE);
        for(int i = 0; i < playerCount; i++) {
            std::string tempName = "player " + std::to_string(i);
            list.emplace_back(currentGame, defaultLocation, tempName, ROSE);
        }
    }

    Player& CircularList::getCurrent () {
        return *it;
    };

    void CircularList::next() {
        it++;
        if(it == list.end()) {
            it = list.begin();
        }
    }
}
