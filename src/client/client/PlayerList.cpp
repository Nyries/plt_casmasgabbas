//
// Created by louismmassin on 12/18/24.
//
#include "PlayerList.h"
namespace client {
    PlayerList::PlayerList(std::vector<Player *> &list):list(move(list)), currentPlayer(list.begin) {
        it = list.begin;
    }

    Player *PlayerList::getCurrent() {
        return *it;
    }

    void PlayerList::next() {
        ++it;
        if (it == list.end()) {
            it = list.begin();
        }
    }

}