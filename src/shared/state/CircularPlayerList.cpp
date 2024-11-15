//
// Created by louismmassin on 11/4/24.
//
#include "CircularPlayerList.h"

#include <vector>

namespace state {
    CircularPlayerList::CircularPlayerList(State& currentGame, int playerCount): it(list.begin()), currentPlayer(list.front()) {
        list.reserve(playerCount);
        for(int i = 0; i < playerCount; i++) {
            std::string tempName = "player " + std::to_string(i);
            list.emplace_back(currentGame, tempName, ROSE);
        }
    }

    PlayerInfo& CircularPlayerList::getCurrent () {
        return *it;
    };

    void CircularPlayerList::next() {
        it++;
        if(it == list.end()) {
            it = list.begin();
        }
    }

    int CircularPlayerList::size() {
        return list.size();
    }

}
