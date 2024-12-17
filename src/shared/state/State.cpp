//
// Created by louismmassin on 11/8/24.
//
#include "State.h"

#include <fstream>
#include <json/json.h>

namespace state {
    State::State(const std::string& stateJsonPath): accusationSuccess(false), envelope()
    {
        std::ifstream file(stateJsonPath);
        Json::Value stateJsonData;
        file >> stateJsonData;
        file.close();

        players = new CircularPlayerList(stateJsonData["playersCount"].asInt());
        map = new Map(stateJsonData["mapJsonPath"].asString());
    }

    Map* State::getMap() {
        return map;
    }

    CircularPlayerList *State::getPlayerList()
    {
        return this->players;
    }

    std::vector<Card> &State::getEnvelope()
    {
        return this->envelope;
    }

    void State::setCircularPlayerList(std::vector<std::tuple<std::string, int, int>> players)
    {
        this->players = new CircularPlayerList(players);
    }
}
