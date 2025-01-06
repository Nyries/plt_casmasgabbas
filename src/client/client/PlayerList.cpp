//
// Created by louismmassin on 12/18/24.
//
#include "PlayerList.h"
namespace client {
    PlayerList::PlayerList(std::vector<std::unique_ptr<Player>> &vec):vec(move(vec)), currentPlayer(**vec.begin()) {
        it = vec.begin();
    }

    Player& PlayerList::getCurrent() {
        return **it;
    }

    void PlayerList::next() {
        ++it;
        if (it == vec.end()) {
            it = vec.begin();
        }
    }

}