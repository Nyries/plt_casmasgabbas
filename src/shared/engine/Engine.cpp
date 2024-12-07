//
// Created by louismmassin on 11/18/24.
//

#include "state.h"
#include "engine.h"
#include "Engine.h"

#include <iostream>
#include <algorithm>


namespace engine {
    Engine::Engine(state::State &state): state(state), playerList(state.getPlayerList()), map(state.getMap()), currentPlayer(playerList->getCurrent()), envelope(state.getEnvelope()) {
    }

    std::vector<std::tuple<std::string, int, int>> Engine::determinePlayerOrder(std::vector<std::tuple<std::string, int, int>> players, int numberOfPlayers)
    {
        for (int i=0; i<numberOfPlayers; i++){
            int dice = UtilityFunctions::randomInt(6) + 1 + UtilityFunctions::randomInt(6) + 1;
            players.at(i) = std::make_tuple(std::get<0>(players.at(i)), dice, 0);
        }
        std::sort(players.begin(), players.end(), [](const std::tuple<std::string, int, int>& a, const std::tuple<std::string, int, int>& b) {
            return std::get<1>(b) < std::get<1>(a);
        });
        return players;
    }

    void Engine::dealCards() {

        std::vector<state::SuspectCard> suspectCardsVector;
        std::vector<state::WeaponCard> weaponCardsVector;
        std::vector<state::RoomCard> roomCardsVector;

        // VECTOR OF SUSPECTS
        suspectCardsVector.emplace_back(state::ROSE);
        suspectCardsVector.emplace_back(state::PERVENCHE);
        suspectCardsVector.emplace_back(state::LEBLANC);
        suspectCardsVector.emplace_back(state::OLIVE);
        suspectCardsVector.emplace_back(state::MOUTARDE);
        suspectCardsVector.emplace_back(state::VIOLET);

        // VECTOR OF WEAPONS
        weaponCardsVector.emplace_back(state::CANDLESTICK);
        weaponCardsVector.emplace_back(state::PISTOL);
        weaponCardsVector.emplace_back(state::ROPE);
        weaponCardsVector.emplace_back(state::LEAD_PIPE);
        weaponCardsVector.emplace_back(state::KNIFE);
        weaponCardsVector.emplace_back(state::WRENCH);

        // VECTOR OF ROOMS

        roomCardsVector.emplace_back(state::STUDY);
        roomCardsVector.emplace_back(state::HALL);
        roomCardsVector.emplace_back(state::LIVING_ROOM);
        roomCardsVector.emplace_back(state::DINING_ROOM);
        roomCardsVector.emplace_back(state::KITCHEN);
        roomCardsVector.emplace_back(state::BATHROOM);
        roomCardsVector.emplace_back(state::GARAGE);
        roomCardsVector.emplace_back(state::GAME_ROOM);
        roomCardsVector.emplace_back(state::BEDROOM);


        int randomSuspect = UtilityFunctions::randomInt(5);
        int randomWeapon = UtilityFunctions::randomInt(5);
        int randomRoom = UtilityFunctions::randomInt(8);

        envelope.push_back(std::move(suspectCardsVector[randomSuspect]));
        suspectCardsVector.erase(suspectCardsVector.begin()+randomSuspect);

        envelope.push_back(std::move(weaponCardsVector[randomWeapon]));
        weaponCardsVector.erase(weaponCardsVector.begin()+randomWeapon);

        envelope.push_back(std::move(roomCardsVector[randomRoom]));
        roomCardsVector.erase(roomCardsVector.begin()+randomSuspect);


        std::vector<state::Card> allCards;
        allCards.reserve(suspectCardsVector.size()+weaponCardsVector.size()+roomCardsVector.size());

        allCards.insert(allCards.end(), suspectCardsVector.begin(), suspectCardsVector.end());
        allCards.insert(allCards.end(), weaponCardsVector.begin(), weaponCardsVector.end());
        allCards.insert(allCards.end(), roomCardsVector.begin(), roomCardsVector.end());

        while (!allCards.empty()) {
            int randomIndex = UtilityFunctions::randomInt(allCards.size());
            playerList->getCurrent().giveCard(allCards.at(randomIndex));
            allCards.erase(allCards.begin()+randomIndex);
            playerList->next();
        }
    }

    void Engine::distributionCharacters () {
        int numberOfPlayer = playerList->size();
        std::vector<state::Suspect> SuspectsVector = {state::ROSE,state::PERVENCHE, state::LEBLANC, state::OLIVE, state::MOUTARDE, state::VIOLET} ;
        state::PlayerInfo* currentPlayer = &playerList->getCurrent();
        int players = 1;
        while (players!=numberOfPlayer+1) {
            currentPlayer->setIdentity(SuspectsVector.at(players));
            playerList->next();
            currentPlayer = &playerList->getCurrent();
        }
    }

    std::vector<int> Engine::dice () {
        int die1 = UtilityFunctions::randomInt(5)+1;
        int die2 = UtilityFunctions::randomInt(5)+1;
        std::vector<int> dice;
        dice.push_back(die1);
        dice.push_back(die2);
        return dice;
    }





}


