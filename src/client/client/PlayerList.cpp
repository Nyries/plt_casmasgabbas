//
// Created by louismmassin on 12/18/24.
//
#include "PlayerList.h"
namespace client {
    PlayerList::PlayerList(std::vector<std::unique_ptr<Player>> &vec):vec(move(vec)), it(this->vec){

    }

    Player& PlayerList::getCurrent() {
        return **it;
    }

    void PlayerList::next() {
        ++it;
    }

    engine::CircularIterator<std::unique_ptr<Player> > PlayerList::getIterator() {
        return it;
    }

}