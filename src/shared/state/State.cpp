//
// Created by louismmassin on 11/8/24.
//
#include "State.h"
#include <tuple>
#include <algorithm>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <json/json.h>

#include "RoomCard.h"
#include "SuspectCard.h"
#include "WeaponCard.h"

namespace state {
    State::State(const std::string& stateJsonPath): accusationSuccess(false), envelope()
    {   

        std::ifstream file(stateJsonPath);
        Json::Value stateJsonData;
        file >> stateJsonData;
        file.close();
        std::cout << "oui" << std::endl;
        

        players = new CircularPlayerList(stateJsonData["playersCount"].asInt());
        map = new Map(stateJsonData["mapJsonPath"].asString());
    }


    void State::determinePlayerOrder() {
        players->shuffle();
    }


    std::vector<Card>& State::createEnvelope (int envelopeSuspect, int envelopeWeapon, int envelopeRoom) {
        std::vector<SuspectCard> suspectCardsVector;
        std::vector<WeaponCard> weaponCardsVector;
        std::vector<RoomCard> roomCardsVector;

        // VECTOR OF SUSPECTS
        suspectCardsVector.emplace_back(ROSE);
        suspectCardsVector.emplace_back(PERVENCHE);
        suspectCardsVector.emplace_back(LEBLANC);
        suspectCardsVector.emplace_back(OLIVE);
        suspectCardsVector.emplace_back(MOUTARDE);
        suspectCardsVector.emplace_back(VIOLET);

        // VECTOR OF WEAPONS
        weaponCardsVector.emplace_back(CANDLESTICK);
        weaponCardsVector.emplace_back(PISTOL);
        weaponCardsVector.emplace_back(ROPE);
        weaponCardsVector.emplace_back(LEAD_PIPE);
        weaponCardsVector.emplace_back(KNIFE);
        weaponCardsVector.emplace_back(WRENCH);


        // VECTOR OF ROOMS
        roomCardsVector.emplace_back(STUDY);
        roomCardsVector.emplace_back(HALL);
        roomCardsVector.emplace_back(LIVING_ROOM);
        roomCardsVector.emplace_back(DINING_ROOM);
        roomCardsVector.emplace_back(KITCHEN);
        roomCardsVector.emplace_back(BATHROOM);
        roomCardsVector.emplace_back(GARAGE);
        roomCardsVector.emplace_back(GAME_ROOM);
        roomCardsVector.emplace_back(BEDROOM);

        /// Put in the envelope the 3 cards

        envelope.push_back(std::move(suspectCardsVector[envelopeSuspect]));
        suspectCardsVector.erase(suspectCardsVector.begin()+envelopeSuspect);
        envelope.push_back(std::move(weaponCardsVector[envelopeWeapon]));
        weaponCardsVector.erase(weaponCardsVector.begin()+envelopeWeapon);
        envelope.push_back(std::move(roomCardsVector[envelopeRoom]));
        roomCardsVector.erase(roomCardsVector.begin()+envelopeRoom);

        /// creation of a vector with all the cards BUT those in the envelope

        std::vector<Card> allCards;
        allCards.reserve(suspectCardsVector.size()+weaponCardsVector.size()+roomCardsVector.size());

        allCards.insert(allCards.end(), suspectCardsVector.begin(), suspectCardsVector.end());
        allCards.insert(allCards.end(), weaponCardsVector.begin(), weaponCardsVector.end());
        allCards.insert(allCards.end(), roomCardsVector.begin(), roomCardsVector.end());

        return allCards;
    }

    void State::generateDeck (std::vector<Card>& allCards) {
        int size = allCards.size();
        int numberOfPlayer = players->size();

        std::random_shuffle(allCards.begin(),allCards.end());
        int remainder = size % numberOfPlayer;
        int quotient = (size-remainder)/numberOfPlayer;
        auto begin = allCards.begin();
        auto end = allCards.begin();
        int nbcard = quotient;

        for (int i=0; i<numberOfPlayer;i++) {
            if (i<remainder) {
                nbcard = quotient +1; // les premiers joueurs ont une carte en plus
            }
            for (int j=0;j<nbcard; j++) {
                players->getCurrent().giveCard(allCards.back());
                allCards.pop_back();
            }
            players->next();
        }

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
