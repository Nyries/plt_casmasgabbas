//
// Created by louismmassin on 11/4/24.
//
#include "CircularLinkedList.h"

#include <deque>

namespace state {
    CircularLinkedList::CircularLinkedList(std::deque<std::shared_ptr<Player> > &listOfPlayers): list(std::move(listOfPlayers)), currentPlayer(*listOfPlayers.front()), it(listOfPlayers.begin()) {
    }

    Player& CircularLinkedList::getCurrent () {
        return **it;
    };

    void CircularLinkedList::next() {
        it++;
        if(it == list.end()) {
            it = list.begin();
        }
    }

}
