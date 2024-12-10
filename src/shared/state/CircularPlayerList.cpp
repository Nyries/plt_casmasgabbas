//
// Created by louismmassin on 11/4/24.
//
#include "CircularPlayerList.h"

#include <vector>
#include <iostream>
#include <string>
#include <tuple>



namespace state {
    using std::get;
    CircularPlayerList::CircularPlayerList(const int playerCount): currentPlayer(list.front()) {
        list.reserve(playerCount);
        it = list.begin();
        for(int i = 0; i < playerCount; i++) {
            std::string tempName = "player " + std::to_string(i);
            list.emplace_back(tempName, ROSE);
        }
    }

    CircularPlayerList::CircularPlayerList(std::vector<std::tuple<std::string, int, int>> players): currentPlayer(list.front())
    {
        int numberOfPlayers = players.size();
        list.reserve(numberOfPlayers);
        it = list.begin();
        for (int i = 0; i<numberOfPlayers; i++){
            list.emplace_back(std::get<0>(players.at(i)), Suspect(std::get<2>(players.at(i))));
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
