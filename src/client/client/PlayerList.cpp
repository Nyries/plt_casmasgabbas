//
// Created by louismmassin on 12/18/24.
//
#include "PlayerList.h"

#include <algorithm>
#include <stdexcept>

namespace client {
    PlayerList::PlayerList(std::vector<std::unique_ptr<Player>> &vec):vec(move(vec)), current(this->vec.begin()){

    }

    Player& PlayerList::getCurrent() {
        return **current;
    }

    void PlayerList::next() {
        ++current;
        if (current == vec.end()) {
            current = vec.begin();
        }
    }

    std::vector<std::unique_ptr<Player> >::iterator PlayerList::getIterator() const{
        return current;
    }


    void PlayerList::setCurrent(const std::unique_ptr<Player> &element) {
        current = std::find_if(vec.begin(), vec.end(), [&element](const auto& i) {
            return &i == &element;
        });
        if (current == vec.end()) {
            throw std::runtime_error("element not found in vector");
        }
    }

    std::vector<std::unique_ptr<Player> > &PlayerList::getVector() {
        return vec;
    }

    void PlayerList::incrementIterator(std::vector<std::unique_ptr<Player> >::iterator &iterator) {
        ++iterator;
        if (iterator == vec.end()) {
            iterator = vec.begin();
        }
    }


}
