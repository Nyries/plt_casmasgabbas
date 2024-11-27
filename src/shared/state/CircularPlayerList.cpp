//
// Created by louismmassin on 11/4/24.
//
#include "CircularPlayerList.h"

#include <vector>

namespace state {
    CircularPlayerList::CircularPlayerList(const int playerCount): currentPlayer(list.front()) {
        list.reserve(playerCount);
        it = list.begin();
        for(int i = 0; i < playerCount; i++) {
            std::string tempName = "player " + std::to_string(i);
            list.emplace_back(tempName, ROSE);
        }
    }

    PlayerInfo& CircularPlayerList::getCurrent () {
        return *it;
    }

    void CircularPlayerList::next() {
        ++it;
        if(it == list.end()) {
            it = list.begin();
        }
    }

    int CircularPlayerList::size() {
        return list.size();
    }

}
